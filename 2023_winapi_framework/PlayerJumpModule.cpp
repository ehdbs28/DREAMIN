#include "pch.h"
#include "PlayerJumpModule.h"
#include "Rigidbody.h"
#include "ModuleController.h"
#include "Object.h"
#include "TimeMgr.h"

PlayerJumpModule::PlayerJumpModule(ModuleController* _controller)
	: PlayerAirModule(_controller)
	, m_fJumpPower(-540.f)
	, m_pRigidbody(nullptr)
{
	m_pRigidbody = m_pController->GetOwner()->GetRigidbody();
}

PlayerJumpModule::~PlayerJumpModule()
{
}

void PlayerJumpModule::EnterModule()
{
	m_pRigidbody->SetVelocity(Vec2(0.f, m_fJumpPower));
	BaseModule::EnterModule();
}

void PlayerJumpModule::UpdateModule()
{
	PlayerAirModule::UpdateModule();
	if (m_pRigidbody->GetVelocity().y >= 0.f) {
		m_pController->ChangeModule(L"FallModule");
		return;
	}
}

void PlayerJumpModule::ExitModule()
{
	BaseModule::ExitModule();
}
