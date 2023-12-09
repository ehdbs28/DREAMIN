#include "pch.h"
#include "DamageCaster.h"
#include "EventMgr.h"

DamageCaster::DamageCaster()
	: OnDamageOverCallback(nullptr)
	, m_pOwner(nullptr)
	, m_maxHealth(0)
	, m_currentHealth(0)
{
}

DamageCaster::~DamageCaster()
{
	OnDamageOverCallback = nullptr;
}

void DamageCaster::OnDamage(float _damage)
{
	m_currentHealth -= _damage;
	if (m_currentHealth <= 0.f) {
		if (OnDamageOverCallback != nullptr) {
			OnDamageOverCallback();
		}
		EventMgr::GetInst()->DeleteObject(m_pOwner);
	}
}
