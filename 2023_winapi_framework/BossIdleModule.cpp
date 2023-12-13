#include "pch.h"
#include "BossIdleModule.h"
#include "TimeMgr.h"
#include "ModuleController.h"

BossIdleModule::BossIdleModule(ModuleController* _controller)
	: BaseModule(_controller)
	, m_cooldownTimer(0.f)
	, m_cooldown(0.f)
	, m_minCooldown(3)
	, m_maxCooldown(4)
{
}

BossIdleModule::~BossIdleModule()
{
}

void BossIdleModule::EnterModule()
{
	m_cooldown = (float)(rand() % ((m_maxCooldown - m_minCooldown) * 100) + m_minCooldown * 100) / 100.f;
	m_cooldownTimer = 0.f;

	BaseModule::EnterModule();
}

void BossIdleModule::UpdateModule()
{
	m_cooldownTimer += fDT;
	if (m_cooldownTimer >= m_cooldown) {
		m_pController->ChangeModule(L"PatternModule");
	}
}

void BossIdleModule::ExitModule()
{
	BaseModule::ExitModule();
}
