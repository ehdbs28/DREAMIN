#include "pch.h"
#include "Particle.h"
#include "Texture.h"
#include "Animator.h"
#include "Animation.h"
#include "TimeMgr.h"
#include "EventMgr.h"
#include "ResMgr.h"

Particle::Particle(PARTICLE_TYPE _type, float _duration, bool _repeat)
	: m_type(_type)
	, m_duration(_duration)
	, m_durationTimer(0.f)
	, m_repeat(_repeat)
	, m_pTex(nullptr)
{
	switch (_type)
	{
	case PARTICLE_TYPE::BOSS_DEAD:
		m_pTex = ResMgr::GetInst()->TexLoad(L"BossDeadParticle", L"Texture\\Particle\\BossDeadParticle.bmp");
		break;
	case PARTICLE_TYPE::PLAYER_DEAD:
		m_pTex = ResMgr::GetInst()->TexLoad(L"PlayerDeadParticle", L"Texture\\Particle\\PlayerDeadParticle.bmp");
		break;
	case PARTICLE_TYPE::PLAYER_SHOOT:
		m_pTex = ResMgr::GetInst()->TexLoad(L"ShootParticle", L"Texture\\Particle\\ShootParticle.bmp");
		break;
	case PARTICLE_TYPE::BULLET_DESTROY:
		m_pTex = ResMgr::GetInst()->TexLoad(L"BulletDestroyParticle", L"Texture\\Particle\\BulletDestroyParticle.bmp");
		break;
	case PARTICLE_TYPE::BOSS_SHOOT:
		m_pTex = ResMgr::GetInst()->TexLoad(L"BossShootParticle", L"Texture\\Particle\\BossShootParticle.bmp");
		break;
	}

	if (m_pTex == nullptr) {
		return;
	}

	int width = m_pTex->GetWidth();
	int frame = width / 16;
	m_duration *= frame;

	CreateAnimator();
	GetAnimator()->CreateAnim(L"Play", m_pTex, Vec2(0, 0), Vec2(16, 16), Vec2(16, 0), frame, _duration);
	GetAnimator()->PlayAnim(L"Play", _repeat);
}

Particle::~Particle()
{
}

void Particle::Update()
{
	m_durationTimer += fDT;
	GetAnimator()->Update();
	if (m_durationTimer > m_duration) {
		EventMgr::GetInst()->DeleteObject(this);
	}
}

void Particle::Render(HDC _dc)
{
	Component_Render(_dc);
}
