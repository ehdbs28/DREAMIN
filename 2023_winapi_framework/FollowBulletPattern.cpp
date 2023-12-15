#include "pch.h"
#include "FollowBulletPattern.h"
#include "ModuleController.h"
#include "Player.h"
#include "Boss.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "BossBullet.h"
#include "Particle.h"
#include "CameraManager.h"

FollowBulletPattern::FollowBulletPattern(ModuleController* _controller)
	: BossPattern(_controller)
	, m_bulletCnt(3)
	, m_currentTime(0.f)
	, m_generateDelay(0.35f)
{
}

FollowBulletPattern::~FollowBulletPattern()
{
}

void FollowBulletPattern::ExcutePattern()
{
	if (m_vecBullet.size() < m_bulletCnt) {
		m_currentTime += fDT;
		if (m_currentTime >= m_generateDelay) {
			CameraManager::GetInst()->Shake(10, 0.1f);
			int angle = rand() % 360 * (M_PI / 180.f);
			Vec2 vPos = m_pModuleController->GetOwner()->GetPos();
			vPos += Vec2(cosf(angle), sinf(angle)) * 100 - Vec2(15, 0);

			Particle* particle = new Particle(PARTICLE_TYPE::BOSS_SHOOT, 0.05f, false);
			particle->SetPos(vPos);
			particle->SetScale(Vec2(90, 90));

			const Player* pTarget = ((Boss*)m_pModuleController->GetOwner())->GetTarget();
			BossBullet* bullet = new BossBullet(OBJECT_GROUP::MONSTER, true, pTarget);
			bullet->SetScale(Vec2(90, 90));
			bullet->SetDamage(1);
			bullet->SetPos(vPos);

			m_vecBullet.push_back(bullet);
			SceneMgr::GetInst()->GetCurScene()->AddObject(particle, OBJECT_GROUP::PARTICLE);
			SceneMgr::GetInst()->GetCurScene()->AddObject(bullet, OBJECT_GROUP::BOSS_ATTACK);
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

void FollowBulletPattern::SetExcute()
{
	m_currentTime = 0.f;
	m_vecBullet.clear();
	BossPattern::SetExcute();
}
