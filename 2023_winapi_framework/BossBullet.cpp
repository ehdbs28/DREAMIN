#include "pch.h"
#include "BossBullet.h"
#include "ResMgr.h"
#include "Player.h"
#include "Particle.h"
#include "SceneMgr.h"
#include "Scene.h"

BossBullet::BossBullet(OBJECT_GROUP _ownerObjectGroup, bool _following, Player* _pTarget)
	: Bullet(_ownerObjectGroup)
	, m_following(_following)
	, m_pTarget(_pTarget)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Bullet", L"Texture\\BossBullet.bmp");
}

BossBullet::~BossBullet()
{
}

void BossBullet::Update()
{
	if (m_following) {
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
	particle->SetScale(Vec2(60, 60));
	SceneMgr::GetInst()->GetCurScene()->AddObject(particle, OBJECT_GROUP::PARTICLE);
}
