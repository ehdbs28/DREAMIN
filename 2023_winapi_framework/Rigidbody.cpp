#include "pch.h"
#include "Rigidbody.h"
#include "Object.h"

Rigidbody::Rigidbody()
	: m_pOwner(nullptr)
	, m_force(Vec2(0.f, 0.f))
	, m_fMass(1.f)
	, m_accel(Vec2(0.f, 0.f))
	, m_velocity(Vec2(0.f, 0.f))
	, m_maxVelocity(10.f)
	, m_friction(0.1f)
{
}

Rigidbody::~Rigidbody()
{
}

void Rigidbody::FinalUpdate(float _dt)
{
	m_accel = m_force / m_fMass;
	m_velocity += m_accel * _dt;

	if (m_velocity.x != 0.f || m_velocity.y != 0.f) {
		Vec2 friction = -m_velocity;
		Vec2 frictionDir = friction.Normalized();
		friction = frictionDir * m_friction;

		if (m_velocity.Length() <= friction.Length()) {
			m_velocity = Vec2(0.f, 0.f);
		}
		else {
			m_velocity += friction;
		}
	}

	float velocity = m_velocity.Length();
	if (m_maxVelocity < velocity) {
		m_velocity = m_velocity.Normalize() * m_maxVelocity;
	}

	ApplyVelocity(_dt);
	m_force = Vec2(0.f, 0.f);
}

void Rigidbody::ApplyVelocity(float _dt)
{
	Vec2 vPos = m_pOwner->GetPos();
	vPos += m_velocity;
	m_pOwner->SetPos(vPos);
}
