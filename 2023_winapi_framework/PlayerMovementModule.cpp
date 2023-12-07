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
	, m_inputDir(Vec2(0, 0))
{
}

PlayerMovementModule::~PlayerMovementModule()
{
}

void PlayerMovementModule::EnterModule()
{
	BaseModule::EnterModule();	

	if (m_inputDir.x == -1)
	{
		m_pAnimator->PlayAnim(L"Minsung_Walk_Left_Top", true);
	}
	else if (m_inputDir.x == 1)
	{
		m_pAnimator->PlayAnim(L"Minsung_Walk_Right_Top", true);
	}
}

void PlayerMovementModule::UpdateModule()
{
	SetInputValue();
	if (m_inputDir.x == 0) {
		m_pController->ChangeModule(L"IdleModule");
		return;
	}

	Vec2 velocity = m_pRigidbody->GetVelocity();
	velocity.x = m_inputDir.x * m_fMovementSpeed;
	m_pRigidbody->SetVelocity(velocity);
	PlayerGroundModule::UpdateModule();
}

void PlayerMovementModule::ExitModule()
{
	BaseModule::ExitModule();
	m_pAnimator->StopAnim();
}

void PlayerMovementModule::SetInputValue()
{
	if (KEY_PRESS(KEY_TYPE::LEFT)) {
		m_inputDir.x = -1;
	}
	else if (KEY_PRESS(KEY_TYPE::RIGHT)) {
		m_inputDir.x = 1;
	}
	else {
		m_inputDir.x = 0;
	}
}