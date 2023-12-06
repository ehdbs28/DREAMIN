#include "pch.h"
#include "PlayerGroundModule.h"
#include "KeyMgr.h"
#include "ModuleController.h"
#include "Object.h"

PlayerGroundModule::PlayerGroundModule(ModuleController* _controller)
	: BaseModule(_controller)
{
}

PlayerGroundModule::~PlayerGroundModule()
{
}

void PlayerGroundModule::UpdateModule()
{
	if (m_pController->GetOwner()->IsGround() && KEY_PRESS(KEY_TYPE::X)) {
		m_pController->ChangeModule(L"JumpModule");
		return;
	}

	if (KEY_DOWN(KEY_TYPE::Z)) {
		m_pController->ChangeModule(L"DashModule");
		return;
	}

	if (KEY_PRESS(KEY_TYPE::C)) {
		m_pController->ChangeModule(L"AttackModule");
		return;
	}

	if (!m_pController->GetOwner()->IsGround()) {
		m_pController->ChangeModule(L"FallModule");
		return;
	}
}
