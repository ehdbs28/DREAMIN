#include "pch.h"
#include "DamageCaster.h"
#include "EventMgr.h"
#include "Object.h"
#include "CameraManager.h"

DamageCaster::DamageCaster()
	: m_pOwner(nullptr)
	, m_maxHealth(0)
	, m_currentHealth(0)
{
}

DamageCaster::~DamageCaster()
{
}

void DamageCaster::OnDamage(int _damage)
{
	m_currentHealth -= _damage;
	if (m_currentHealth <= 0.f) {
		CameraManager::GetInst()->Shake(30, 0.25f);
		m_pOwner->DeadHandle();
		EventMgr::GetInst()->DeleteObject(m_pOwner);
	}
}
