#pragma once

class Object;

class Rigidbody
{
public:
	Rigidbody();
	~Rigidbody();

public:
	void FinalUpdate();

public:
	void AddForce(Vec2 _force) { m_force += _force; }
	void SetVelocity(Vec2 _velocity) { m_velocity = _velocity; }
	void AddVelocity(Vec2 _velocity) { m_velocity += _velocity; }
	void SetMaxVelocity(float _maxVelocity) { m_maxVelocity = _maxVelocity; }
	void SetGravityScale(int _gravityScale) { m_gravityScale = _gravityScale; }

public:
	const Vec2& GetVelocity() const { return m_velocity; }
	const int& GetGravityScale() const { return m_gravityScale; }

private:
	void ApplyVelocity();
	Vec2 ClampPosition(Vec2 _vPos);

private:
	Object* m_pOwner;
	friend class Object;

	Vec2 m_force;
	float m_fMass;
	Vec2 m_accel;

	Vec2 m_velocity;

	float m_maxVelocity;

	float m_gravity;
	int m_gravityScale;

};

