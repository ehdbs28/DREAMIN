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
{
}

PlayerAirModule::~PlayerAirModule()
{
}

void PlayerAirModule::UpdateModule()
{
	BaseModule::UpdateModule();

	int front = m_pController->GetOwner()->GetFrontDir();

	if (KEY_PRESS(KEY_TYPE::LEFT)) {
		front = -1;
		
	}
	else if (KEY_PRESS(KEY_TYPE::RIGHT)) {
		front = 1;
	}
	else {
		front = 0;
	}

	if (KEY_DOWN(KEY_TYPE::Z)) {
		m_pController->ChangeModule(L"DashModule");
		return;
	}

	if (KEY_PRESS(KEY_TYPE::C)) {
		m_pController->ChangeModule(L"AttackModule");
		return;
	}

	if (front == 0) {
		return;
	}

	Vec2 velocity = m_pRigidbody->GetVelocity();
	velocity.x = front * m_fMovementSpeed;
	m_pRigidbody->SetVelocity(velocity);
	m_pController->GetOwner()->SetFront(front);
}