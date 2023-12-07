#include "pch.h"
#include "PlayerFallModule.h"
#include "ModuleController.h"
#include "Object.h"
#include "Animator.h"


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
	if (m_pController->GetOwner()->IsGround()) {
		m_pController->ChangeModule(L"IdleModule");
		return;
	}
	PlayerAirModule::UpdateModule();
}

void PlayerFallModule::ExitModule()
{
	BaseModule::ExitModule();
}
