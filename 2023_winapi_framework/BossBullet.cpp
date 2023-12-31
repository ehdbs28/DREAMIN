#include "pch.h"
#include "BossBullet.h"
#include "ResMgr.h"
#include "Player.h"
#include "Particle.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "TimeMgr.h"

BossBullet::BossBullet(OBJECT_GROUP _ownerObjectGroup, bool _following, const Player* _pTarget, float _lifeTime)
	: Bullet(_ownerObjectGroup)
	, m_following(_following)
	, m_pTarget(_pTarget)
	, m_lifeTime(_lifeTime)
	, m_currentTime(0.f)
{
	if (m_following) {
		SetSpeed(200.f);
	}
	m_pTex = ResMgr::GetInst()->TexLoad(L"BossBullet", L"Texture\\BossBullet.bmp");
}

BossBullet::~BossBullet()
{
}

void BossBullet::Update()
{
	if (m_following) {
		m_currentTime += fDT;
		if (m_currentTime >= m_lifeTime) {
			Destroy();
			return;
		}

		Vec2 vPos = GetPos();
		Vec2 vTargetPos = m_pTarget->GetPos();
		SetDir((vTargetPos - vPos).Normalized());
	}
	Bullet::Update();
}

void BossBullet::GenerateDestroyParticle()
{
	Particle* particle = new Particle(PARTICLE_TYPE::BOSS_BULLET_DESTROY, 0.05f, false);
	particle->SetPos(GetPos());
	particle->SetScale(Vec2(80, 80));
	SceneMgr::GetInst()->GetCurScene()->AddObject(particle, OBJECT_GROUP::PARTICLE);
}
