#include "pch.h"
#include "PlayerAirModule.h"
#include "KeyMgr.h"
#include "Rigidbody.h"
#include "ModuleController.h"
#include "Object.h"
#include "TimeMgr.h"

PlayerAirModule::PlayerAirModule(ModuleController* _controller)
	: BaseModule(_controller)
	, m_fMovementSpeed(300.f)
	, m_inputDir(Vec2(0.f, 0.f))
{
}

PlayerAirModule::~PlayerAirModule()
{
}

void PlayerAirModule::UpdateModule()
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

	if (KEY_DOWN(KEY_TYPE::Z)) {
		m_pController->ChangeModule(L"DashModule");
		return;
	}

	Rigidbody* rigid = m_pController->GetOwner()->GetRigidbody();
	Vec2 velocity = rigid->GetVelocity();
	velocity.x = (float)m_inputDir.x * m_fMovementSpeed;
	rigid->SetVelocity(velocity);
}