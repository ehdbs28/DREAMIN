#include "pch.h"
#include "PlayerMovementModule.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "ModuleController.h"
#include "Object.h"
#include "Rigidbody.h"
#include "PlayerDashModule.h"
#include "Player.h"
#include "Animator.h"

PlayerMovementModule::PlayerMovementModule(ModuleController* _controller)
	: PlayerGroundModule(_controller)
	, m_fMovementSpeed(300.f)
{
	SetAnimationKey(L"Minsung_Walk");
}

PlayerMovementModule::~PlayerMovementModule()
{
}

void PlayerMovementModule::EnterModule()
{
	BaseModule::EnterModule();	
}

void PlayerMovementModule::UpdateModule()
{
	int front = m_pController->GetOwner()->GetFrontDir();
	
	if (KEY_PRESS(KEY_TYPE::LEFT)) {
		front = -1;
	}
	else if (KEY_PRESS(KEY_TYPE::RIGHT)) {
		front = 1;
	}
	else {
		m_pController->ChangeModule(L"IdleModule");
		return;
	}

	Vec2 velocity = m_pRigidbody->GetVelocity();
	velocity.x = front * m_fMovementSpeed;
	m_pRigidbody->SetVelocity(velocity);
	m_pController->GetOwner()->SetFront(front);
	PlayerGroundModule::UpdateModule();
}

void PlayerMovementModule::ExitModule()
{
	BaseModule::ExitModule();
}