#include "pch.h"
#include "DamageCaster.h"

DamageCaster::DamageCaster()
	: OnDamageOverCallback(nullptr)
	, m_pOwner(nullptr)
	, m_maxHealth(0)
	, m_currentHealth(0)
{
}

DamageCaster::~DamageCaster()
{
}

void DamageCaster::OnDamage(float _damage)
{
}
