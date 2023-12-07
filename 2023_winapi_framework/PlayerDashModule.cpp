#include "pch.h"
#include "PlayerDashModule.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "ModuleController.h"
#include "Object.h"
#include "Rigidbody.h"
#include "Player.h"
#include "PlayerMovementModule.h"

PlayerDashModule::PlayerDashModule(ModuleController* _controller)
	: BaseModule(_controller)
	, m_dashDir(Vec2(0.f, 0.f))
	, m_dashSpeed(5000.f)
	, m_dashDuration(0.2f)
	, m_dashDurationTimer(0.f)
{
}

PlayerDashModule::~PlayerDashModule()
{
}

void PlayerDashModule::EnterModule()
{
	BaseModule::EnterModule();

	m_dashDir = Vec2(0.f, 0.f);
	m_dashDurationTimer = 0.f;

	if (KEY_PRESS(KEY_TYPE::UP)) {
		m_dashDir.y = -1;
	}
	else if (KEY_PRESS(KEY_TYPE::DOWN)) {
		m_dashDir.y = 1;
	}
	else if (KEY_PRESS(KEY_TYPE::LEFT)) {
		m_dashDir.x = -1;
	}
	else if (KEY_PRESS(KEY_TYPE::RIGHT)) {
		m_dashDir.x = 1;
	}

	Rigidbody* rigidbody = m_pController->GetOwner()->GetRigidbody();

	if (m_dashDir.y != 0 && rigidbody->GetGravityScale() != m_dashDir.y) {
		rigidbody->SetGravityScale(m_dashDir.y);
	}

	rigidbody->SetVelocity(m_dashDir * m_dashSpeed);
}

void PlayerDashModule::UpdateModule()
{
	m_dashDurationTimer += fDT;
	if (m_dashDurationTimer >= m_dashDuration) {
		m_pController->ChangeModule(L"IdleModule");
		return;
	}
}

void PlayerDashModule::ExitModule()
{
	BaseModule::ExitModule();
}