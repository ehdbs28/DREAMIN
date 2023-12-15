#include "pch.h"
#include "WallAttack.h"
#include "Texture.h"
#include "Collider.h"
#include "Animator.h"
#include "TimeMgr.h"
#include "Object.h"
#include "DamageCaster.h"

WallAttack::WallAttack(float _enableTimer, float _attackTimer)
	: m_pTex(nullptr)
	, m_currentTime(0.f)
	, m_enableTimer(_enableTimer)
	, m_attackTimer(_attackTimer)
	, m_isAttack(false)
{
	CreateCollider();
	//GetCollider()->SetScale();

	CreateAnimator();
	GetAnimator()->CreateAnim(L"Enable", m_pTex, Vec2(0, 0), Vec2(16, 16), Vec2(16, 0), 9, m_enableTimer / 9.f);
	GetAnimator()->CreateAnim(L"Disable", m_pTex, Vec2(144, 0), Vec2(16, 16), Vec2(-16, 0), 9, m_enableTimer / 9.f);
	GetAnimator()->PlayAnim(L"Enable", false);
}

WallAttack::~WallAttack()
{
}

void WallAttack::Update()
{
	if (!m_isAttack) {
		m_currentTime += fDT;
		if (m_currentTime >= m_enableTimer) {
			m_isAttack = true;
			m_currentTime = 0.f;
		}
	}
	else {
		m_currentTime += fDT;
		if (m_currentTime >= m_attackTimer) {
			GetAnimator()->PlayAnim(L"Disable", false);
		}
	}
}

void WallAttack::Render(HDC _dc)
{
	Component_Render(_dc);
}

void WallAttack::StayCollision(Collider* _pOther)
{
	if (!m_isAttack) {
		return;
	}

	if (_pOther->GetObj()->GetName() == L"Player") {
		_pOther->GetObj()->GetDamageCaster()->OnDamage(1);
	}
}
