#include "pch.h"
#include "PlayerIdleModule.h"
#include "KeyMgr.h"
#include "ModuleController.h"

PlayerIdleModule::PlayerIdleModule(ModuleController* _controller)
	: BaseModule(_controller)
{
}

PlayerIdleModule::~PlayerIdleModule()
{
}

void PlayerIdleModule::EnterModule()
{
}

void PlayerIdleModule::UpdateModule()
{
	if (KEY_DOWN(KEY_TYPE::LEFT) || KEY_DOWN(KEY_TYPE::RIGHT)) {
		m_pController->ChangeModule(L"MovementModule");
	}
}

void PlayerIdleModule::ExitModule()
{
}
