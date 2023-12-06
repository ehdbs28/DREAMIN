#include "pch.h"
#include "PlayerMovementModule.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "ModuleController.h"
#include "Object.h"
#include "Rigidbody.h"
#include "PlayerDashModule.h"
#include "Player.h"

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
}

void PlayerMovementModule::UpdateModule()
{
	SetInputValue();
	if (m_inputDir.x == 0) {
		m_pController->ChangeModule(L"IdleModule");
		return;
	}

	Rigidbody* pRigidbody = m_pController->GetOwner()->GetRigidbody();
	Vec2 velocity = pRigidbody->GetVelocity();
	velocity.x = m_inputDir.x * m_fMovementSpeed;
	pRigidbody->SetVelocity(velocity);
	PlayerGroundModule::UpdateModule();
}

void PlayerMovementModule::ExitModule()
{
	BaseModule::ExitModule();
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