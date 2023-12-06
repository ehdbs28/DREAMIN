#include "pch.h"
#include "Rigidbody.h"
#include "Object.h"
#include "TimeMgr.h"

Rigidbody::Rigidbody()
	: m_pOwner(nullptr)
	, m_force(Vec2(0.f, 0.f))
	, m_fMass(1.f)
	, m_accel(Vec2(0.f, 0.f))
	, m_velocity(Vec2(0.f, 0.f))
	, m_maxVelocity(10000.f)
	, m_gravity(1400.f)
	, m_gravityScale(1)
{
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::FinalUpdate()
{
	if (!m_pOwner->IsGround()) {
		m_force.y = m_gravity * m_gravityScale;
	}
	
	m_accel = m_force / m_fMass;
	m_velocity += m_accel * fDT;

	float velocity = m_velocity.Length();
	if (m_maxVelocity < velocity) {
		m_velocity = m_velocity.Normalize() * m_maxVelocity;
	}

	ApplyVelocity();
	m_force = Vec2(0.f, 0.f);
}

void Rigidbody::ApplyVelocity()
{
	Vec2 vPos = m_pOwner->GetPos();
	vPos += m_velocity * fDT;
	vPos = ClampPosition(vPos);
	m_pOwner->SetPos(vPos);
}

Vec2 Rigidbody::ClampPosition(Vec2 _vPos)
{
	if (_vPos.x < 0.f + m_pOwner->GetScale().x / 2.f) {
		_vPos.x = 0.f + m_pOwner->GetScale().x / 2.f;
	}
	else if (_vPos.x > WINDOW_WIDTH - m_pOwner->GetScale().x / 2.f) {
		_vPos.x = WINDOW_WIDTH - m_pOwner->GetScale().x / 2.f;
	}
	return _vPos;
}