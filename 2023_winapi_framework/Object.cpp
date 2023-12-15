#include "pch.h"
#include "Object.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "Animator.h"
#include "Rigidbody.h"
#include "DamageCaster.h"

Object::Object()
	: m_pCollider(nullptr)
	, m_vPos{}
	, m_vScale{}
	, m_fAngle(0.f)
	, m_pAnimator(nullptr)
	, m_pRigidbody(nullptr)
	, m_pDamageCaster(nullptr)
	, m_isGround(false)
	, m_frontDir(1)
	, m_isDead(false)
{
}

Object::~Object()
{
	if (nullptr != m_pCollider)
		delete m_pCollider;
	if (nullptr != m_pAnimator)
		delete m_pAnimator;
	if (nullptr != m_pDamageCaster)
		delete m_pDamageCaster;
}

void Object::CreateCollider()
{
	m_pCollider = new Collider;
	m_pCollider->m_pOwner = this;
}

void Object::CreateAnimator()
{
	m_pAnimator = new Animator;
	m_pAnimator->m_pOwner = this;
}

void Object::CreateRigidbody()
{
	m_pRigidbody = new Rigidbody;
	m_pRigidbody->m_pOwner = this;
}

void Object::CreateDamageCaster()
{
	m_pDamageCaster = new DamageCaster;
	m_pDamageCaster->m_pOwner = this;
}

void Object::DeadHandle()
{
}

void Object::FinalUpdate()
{
	if (m_pCollider)
		m_pCollider->FinalUpdate();
	if (m_pRigidbody)
		m_pRigidbody->FinalUpdate();
}

void Object::EnterCollision(Collider* _pOther)
{
}

void Object::ExitCollision(Collider* _pOther)
{
}

void Object::StayCollision(Collider* _pOther)
{

}

void Object::Component_Render(HDC _dc)
{
	if (nullptr != m_pAnimator)
		m_pAnimator->Render(_dc);
	if (nullptr != m_pCollider)
		m_pCollider->Render(_dc);
}