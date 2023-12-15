#include "pch.h"
#include "RadialBulletPattern.h"
#include "Particle.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "BossBullet.h"
#include "TimeMgr.h"
#include "ModuleController.h"
#include "CameraManager.h"

RadialBulletPattern::RadialBulletPattern(ModuleController* _controller)
	: BossPattern(_controller)
	, m_bulletCnt(12)
	, m_angle(0)
	, m_interval(360 / m_bulletCnt)
	, m_rotateTime(0.f)
	, m_currentTime(0.f)
	, m_rotateTimer(1.f)
	, m_generateDelay(0.15f)
{
}

RadialBulletPattern::~RadialBulletPattern()
{
}

void RadialBulletPattern::ExcutePattern()
{
	if (m_rotateTime < m_rotateTimer) {
		m_rotateTime += fDT;
		float percent = m_rotateTime / m_rotateTimer;
		float angle = 360 * EaseInOutCubic(percent);
		m_pModuleController->GetOwner()->SetAngle(angle);
	}

	if (m_vecBullet.size() < m_bulletCnt) {
		m_currentTime += fDT;
		if (m_currentTime >= m_generateDelay) {
			CameraManager::GetInst()->Shake(10, 0.1f);

			float fRadian = m_angle * (M_PI / 180.f);
			Vec2 vPos = m_pModuleController->GetOwner()->GetPos();
			Vec2 vBulletPos = vPos + Vec2(cosf(fRadian), sinf(fRadian)) * 100 - Vec2(15, 0);

			Particle* particle = new Particle(PARTICLE_TYPE::BOSS_SHOOT, 0.05f, false);
			particle->SetPos(vBulletPos);
			particle->SetScale(Vec2(90, 90));

			BossBullet* bullet = new BossBullet(OBJECT_GROUP::MONSTER);
			bullet->SetScale(Vec2(90, 90));
			bullet->SetDamage(1);
			bullet->SetPos(vBulletPos);
			bullet->SetDamage(1);
			bullet->SetDir((vBulletPos - vPos).Normalized());

			m_vecBullet.push_back(bullet);
			SceneMgr::GetInst()->GetCurScene()->AddObject(particle, OBJECT_GROUP::PARTICLE);
			SceneMgr::GetInst()->GetCurScene()->AddObject(bullet, OBJECT_GROUP::BOSS_ATTACK);
			m_angle += m_interval;
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

void RadialBulletPattern::SetExcute()
{
	m_angle = 0;
	m_rotateTime = 0.f;
	m_currentTime = 0.f;
	m_vecBullet.clear();
	BossPattern::SetExcute();
}
