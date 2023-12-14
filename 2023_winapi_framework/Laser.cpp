#include "pch.h"
#include "Laser.h"
#include "ResMgr.h"
#include "TimeMgr.h"
#include "Animator.h"
#include "EventMgr.h"
#include "Collider.h"
#include "Object.h"
#include "DamageCaster.h"
#include "LaserPoint.h"
#include "Particle.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Core.h"

Laser::Laser(float _shotDelay, float _shotTimer, float _destroyTimer)
	: m_pLaserTex(nullptr)
	, m_pPoint(nullptr)
	, m_curTime(0.f)
	, m_shotDelay(_shotDelay)
	, m_shotTimer(_shotTimer)
	, m_destroyTimer(_destroyTimer)
	, m_isDestroy(false)
	, m_isShot(false)
{
	m_pLaserTex = ResMgr::GetInst()->TexLoad(L"Laser", L"Texture\\Laser.bmp");
	m_pPoint = new LaserPoint;
	m_pPoint->SetScale(Vec2(30, 30));

	CreateCollider();
	GetCollider()->SetScale(Vec2(800, 100));

	CreateAnimator();
	GetAnimator()->CreateAnim(L"Ready", m_pLaserTex, Vec2(0, 0), Vec2(32, 32), Vec2(32, 0), 1, 0.1f);
	GetAnimator()->CreateAnim(L"Shot", m_pLaserTex, Vec2(0, 32), Vec2(32, 32), Vec2(32, 0), 8, 0.05f);
	GetAnimator()->CreateAnim(L"Destroy", m_pLaserTex, Vec2(0, 64), Vec2(32, 32), Vec2(32, 0), 4, 0.05f);
	GetAnimator()->PlayAnim(L"Ready", true);
}

Laser::~Laser()
{
	delete m_pPoint;
}

void Laser::Update()
{
	m_pPoint->Update();
	GetAnimator()->Update();

	if (!m_isShot) {
		m_curTime += fDT;

		if(m_curTime >= m_shotDelay) {
			Particle* particle = new Particle(PARTICLE_TYPE::BOSS_SHOOT, 0.1f, false);
			particle->SetPos(Vec2(GetPos().x - GetScale().x / 2 + 15, GetPos().y));
			particle->SetScale(Vec2(50, 50));
			SceneMgr::GetInst()->GetCurScene()->AddObject(particle, OBJECT_GROUP::PARTICLE);

			m_pPoint->SetScale(Vec2(125, 125));
			m_pPoint->GetAnimator()->PlayAnim(L"Shot", true);
			GetAnimator()->PlayAnim(L"Shot", false);
			m_isShot = true;
			m_curTime = 0.f;
		}
	}
	else {
		if (m_isDestroy) {
			m_curTime += fDT;
			if (m_curTime >= m_destroyTimer) {
				EventMgr::GetInst()->DeleteObject(this);
			}
		}
		else {
			m_curTime += fDT;
			if (m_curTime >= m_shotTimer) {
				GetAnimator()->PlayAnim(L"Destroy", false);
				m_isDestroy = true;
				m_curTime = 0.f;
			}
		}
	}
}

void Laser::Render(HDC _dc)
{
	m_pPoint->Render(_dc);
	Component_Render(_dc);
}

void Laser::EnterCollision(Collider* _pOther)
{
	if (!m_isShot) {
		return;
	}

	if (_pOther->GetObj()->GetName() == L"Player") {
		_pOther->GetObj()->GetDamageCaster()->OnDamage(1);
	}
}

void Laser::SetPos(Vec2 _pos)
{
	Vec2 vScale = GetScale();
	Object::SetPos(Vec2(_pos.x + vScale.x / 2, _pos.y));
	vScale = m_pPoint->GetScale();
	m_pPoint->SetPos(Vec2(_pos.x + vScale.x / 2, _pos.y));
}
