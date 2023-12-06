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
	: BaseModule(_controller)
	, m_fMovementSpeed(300.f)
	, m_inputDir(Vec2(0, 0))
{
}

PlayerMovementModule::~PlayerMovementModule()
{
}

void PlayerMovementModule::EnterModule()
{
}

void PlayerMovementModule::UpdateModule()
{
	SetInputValue();

	Rigidbody* pRigidbody = m_pController->GetOwner()->GetRigidbody();
	pRigidbody->SetVelocity(m_inputDir * m_fMovementSpeed * fDT);
}

void PlayerMovementModule::ExitModule()
{
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
		m_pController->ChangeModule(L"IdleModule");
	}

	if (KEY_DOWN(KEY_TYPE::X)) {
		if (m_pController->GetOwner()->IsGround()) {
			return;
		}
		m_pController->ChangeModule(L"JumpModule");
	}
}