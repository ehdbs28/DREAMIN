#pragma once

class Object;

class DamageCaster
{
public:
	DamageCaster();
	~DamageCaster();

public:
	void OnDamage(int _damage);

public:
	const int& GetHealth() const { return m_currentHealth; }

public:
	void SetMaxHealth(int _maxHealth) { m_maxHealth = m_currentHealth = _maxHealth; }

public:
	void(*OnDamageOverCallback)();

private:
	Object* m_pOwner;
	friend class Object;

	int m_maxHealth;
	int m_currentHealth;

};

