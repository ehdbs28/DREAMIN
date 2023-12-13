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

Laser::Laser(float _shotDelay, float _shotTimer)
	: m_pLaserTex(nullptr)
	, m_pPoint(nullptr)
	, m_curTime(0.f)
	, m_shotDelay(_shotDelay)
	, m_shotTimer(_shotTimer)
	, m_isShot(false)
{
	m_pLaserTex = ResMgr::GetInst()->TexLoad(L"Laser", L"Texture\\Laser.bmp");
	m_pPoint = new LaserPoint;
	m_pPoint->SetScale(Vec2(25, 25));

	CreateAnimator();
	GetAnimator()->CreateAnim(L"Ready", m_pLaserTex, Vec2(0, 0), Vec2(16, 16), Vec2(16, 0), 1, 0.1f);
	GetAnimator()->CreateAnim(L"Shot", m_pLaserTex, Vec2(0, 16), Vec2(16, 16), Vec2(16, 0), 8, m_shotTimer / 8);
	GetAnimator()->PlayAnim(L"Ready", true);
}

Laser::~Laser()
{
}

void Laser::Update()
{
	m_pPoint->Update();
	GetAnimator()->Update();

	if (!m_isShot) {
		m_curTime += fDT;
		if (m_curTime >= m_shotDelay) {
			GetAnimator()->PlayAnim(L"Shot", false);
			m_isShot = true;
			m_curTime = 0.f;
		}
	}
	else {
		m_curTime += fDT;
		if (m_curTime >= m_shotTimer) {
			EventMgr::GetInst()->DeleteObject(this);
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
