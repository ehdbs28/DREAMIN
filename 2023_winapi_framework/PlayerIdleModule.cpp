#include "pch.h"
#include "PlayerIdleModule.h"
#include "KeyMgr.h"
#include "Rigidbody.h"
#include "Object.h"
#include "ModuleController.h"

PlayerIdleModule::PlayerIdleModule(ModuleController* _controller)
	: PlayerGroundModule(_controller)
{
}

PlayerIdleModule::~PlayerIdleModule()
{
}

void PlayerIdleModule::EnterModule()
{
	Rigidbody* pRigid = m_pController->GetOwner()->GetRigidbody();
	pRigid->SetVelocity(Vec2(0.f, 0.f));
	BaseModule::EnterModule();
}

void PlayerIdleModule::UpdateModule()
{
	PlayerGroundModule::UpdateModule();

	if (KEY_PRESS(KEY_TYPE::LEFT) || KEY_PRESS(KEY_TYPE::RIGHT)) {
		m_pController->ChangeModule(L"MovementModule");
		return;
	}
}

void PlayerIdleModule::ExitModule()
{
	BaseModule::ExitModule();
}
