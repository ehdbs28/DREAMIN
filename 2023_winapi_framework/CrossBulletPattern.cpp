#include "pch.h"
#include "CrossBulletPattern.h"
#include "ModuleController.h"
#include "Particle.h"
#include "BossBullet.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Object.h"
#include "CameraManager.h"

CrossBulletPattern::CrossBulletPattern(ModuleController* _controller)
	: BossPattern(_controller)
	, m_movementPos(Vec2((float)WINDOW_WIDTH / 2.f, (float)WINDOW_HEIGHT / 3.f + 20.f))
	, m_bulletCnt(8)
	, m_currentTime(0.f)
	, m_movementTimer(0.5f)
	, m_generateDelay(0.75f)
	, m_isReadyAttack(false)
{
	m_dirs.push_back(Vec2(1, 0));
	m_dirs.push_back(Vec2(-1, 0));
	m_dirs.push_back(Vec2(0, 1));
	m_dirs.push_back(Vec2(0, -1));
	m_dirs.push_back(Vec2(1, 1).Normalized());
	m_dirs.push_back(Vec2(1, -1).Normalized());
	m_dirs.push_back(Vec2(-1, 1).Normalized());
	m_dirs.push_back(Vec2(-1, -1).Normalized());
}

CrossBulletPattern::~CrossBulletPattern()
{
}

void CrossBulletPattern::ExcutePattern()
{
	if (!m_isReadyAttack) {
		m_currentTime += fDT;
		float percent = m_currentTime / m_movementTimer;
		Vec2 lerp = Vec2::Lerp(m_originPos, m_movementPos, EaseInOutCubic(percent));
		m_pModuleController->GetOwner()->SetPos(lerp);

		if (percent >= 1.f) {
			m_isReadyAttack = true;
			m_currentTime = 0.f;
		}
	}
	else {
		if (m_vecBullet.size() < m_bulletCnt) {
			m_currentTime += fDT;
			if (m_currentTime >= m_generateDelay) {
				CameraManager::GetInst()->Shake(10, 0.1f);
				int size = m_vecBullet.size();
				for (int i = size;  i < size + 4; i++) {
					Vec2 vPos = m_pModuleController->GetOwner()->GetPos();
					vPos += m_dirs[i] * 100 - Vec2(15, 0);

					Particle* particle = new Particle(PARTICLE_TYPE::BOSS_SHOOT, 0.05f, false);
					particle->SetPos(vPos);
					particle->SetScale(Vec2(90, 90));

					BossBullet* bullet = new BossBullet(OBJECT_GROUP::MONSTER);
					bullet->SetScale(Vec2(90, 90));
					bullet->SetDamage(1);
					bullet->SetPos(vPos);
					bullet->SetDamage(1);
					bullet->SetDir(m_dirs[i]);

					m_vecBullet.push_back(bullet);
					SceneMgr::GetInst()->GetCurScene()->AddObject(particle, OBJECT_GROUP::PARTICLE);
					SceneMgr::GetInst()->GetCurScene()->AddObject(bullet, OBJECT_GROUP::BOSS_ATTACK);
				}
				m_currentTime = 0.f;
			}
		}
		else {
			bool isEnd = true;
			for (auto& bullet : m_vecBullet) {
				if (!bullet->GetIsDead()) {
					isEnd = false;
					break;
				}
			}
			m_isExecute = !isEnd;
		}
	}
}

void CrossBulletPattern::SetExcute()
{
	m_originPos = m_pModuleController->GetOwner()->GetPos();
	m_currentTime = 0.f;
	m_vecBullet.clear();
	m_isReadyAttack = false;
	BossPattern::SetExcute();
}
