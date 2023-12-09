#include "pch.h"
#include "PlayerIdleModule.h"
#include "KeyMgr.h"
#include "Rigidbody.h"
#include "Object.h"
#include "ModuleController.h"
#include "Animator.h"
#include "Player.h"

PlayerIdleModule::PlayerIdleModule(ModuleController* _controller)
	: PlayerGroundModule(_controller)
{
	SetAnimationKey(L"Minsung_Idle");
}

PlayerIdleModule::~PlayerIdleModule()
{
}

void PlayerIdleModule::EnterModule()
{
	m_pRigidbody->SetVelocity(Vec2(0.f, 0.f));
	BaseModule::EnterModule();
}

void PlayerIdleModule::UpdateModule()
{
	if (KEY_PRESS(KEY_TYPE::LEFT) || KEY_PRESS(KEY_TYPE::RIGHT)) {
		m_pController->ChangeModule(L"MovementModule");
		return;
	}
	PlayerGroundModule::UpdateModule();
}

void PlayerIdleModule::ExitModule()
{
	BaseModule::ExitModule();
}
