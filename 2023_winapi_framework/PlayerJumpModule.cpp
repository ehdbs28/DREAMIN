#include "pch.h"
#include "PlayerJumpModule.h"
#include "Rigidbody.h"
#include "ModuleController.h"
#include "Object.h"
#include "TimeMgr.h"

PlayerJumpModule::PlayerJumpModule(ModuleController* _controller)
	: PlayerAirModule(_controller)
	, m_fJumpPower(-540.f)
{
}

PlayerJumpModule::~PlayerJumpModule()
{
}

void PlayerJumpModule::EnterModule()
{
	m_pRigidbody->SetVelocity(Vec2(0.f, m_fJumpPower * m_pRigidbody->GetGravityScale()));
	BaseModule::EnterModule();
}

void PlayerJumpModule::UpdateModule()
{
	if (m_pRigidbody->GetVelocity().y >= 0.f) {
		m_pController->ChangeModule(L"FallModule");
		return;
	}
	PlayerAirModule::UpdateModule();
}

void PlayerJumpModule::ExitModule()
{
	BaseModule::ExitModule();
}
