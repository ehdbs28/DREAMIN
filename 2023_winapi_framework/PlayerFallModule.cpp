#include "pch.h"
#include "PlayerFallModule.h"
#include "ModuleController.h"
#include "Object.h"
#include "Animator.h"
#include "Rigidbody.h"
#include "Player.h"

PlayerFallModule::PlayerFallModule(ModuleController* _controller)
	: PlayerAirModule(_controller)
{
	SetAnimationKey(L"Minsung_Jump");
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
