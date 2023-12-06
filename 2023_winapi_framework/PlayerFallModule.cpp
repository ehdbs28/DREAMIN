#include "pch.h"
#include "PlayerFallModule.h"
#include "ModuleController.h"
#include "Object.h"

PlayerFallModule::PlayerFallModule(ModuleController* _controller)
	: PlayerAirModule(_controller)
{
}

PlayerFallModule::~PlayerFallModule()
{
}

void PlayerFallModule::EnterModule()
{
	BaseModule::EnterModule();
}

void PlayerFallModule::UpdateModule()
{
	PlayerAirModule::UpdateModule();
	if (m_pController->GetOwner()->IsGround()) {
		m_pController->ChangeModule(L"IdleModule");
		return;
	}
}

void PlayerFallModule::ExitModule()
{
	BaseModule::ExitModule();
}
