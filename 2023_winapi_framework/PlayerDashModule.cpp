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
	, m_dashDest(Vec2(0, 0))
	, m_dashDurationTimer(0.f)
	, m_dashDuration(0.1f)
	, m_isDash(false)
{
}

PlayerDashModule::~PlayerDashModule()
{
}

void PlayerDashModule::UpdateModule()
{
	InputSetting();

	if (m_isDash) {
		m_dashDurationTimer += fDT;

		if (m_dashDurationTimer > m_dashDuration) {
			Rigidbody* rigidbody = m_pController->GetOwner()->GetRigidbody();
			rigidbody->SetVelocity(Vec2(0.f, 0.f));
			m_isDash = false;
		}
	}
}

void PlayerDashModule::InputSetting()
{
	m_dashDest = m_pController->GetOwner()->GetPos();
	if (KEY_PRESS(KEY_TYPE::UP)) {
		m_dashDest.y = (float)WINDOW_HEIGHT / 5.f + m_pController->GetOwner()->GetScale().y / 2.f;
	}
	else if(KEY_PRESS(KEY_TYPE::DOWN)) {
		m_dashDest.y = (float)WINDOW_HEIGHT - ((float)WINDOW_HEIGHT / 5.f + m_pController->GetOwner()->GetScale().y / 2.f);
	}
	else if (KEY_PRESS(KEY_TYPE::LEFT)) {
		m_dashDest.x = 0.f + m_pController->GetOwner()->GetScale().x / 2.f;
	}
	else if (KEY_PRESS(KEY_TYPE::RIGHT)) {
		m_dashDest.x = WINDOW_WIDTH - m_pController->GetOwner()->GetScale().x / 2.f;
	}

	if (KEY_DOWN(KEY_TYPE::Z)) {
		Dash();
	}
}

void PlayerDashModule::Dash()
{
	if (m_isDash) {
		return;
	}

	m_isDash = true;
	m_dashDurationTimer = 0.f;

	Player* player = (Player*)m_pController->GetOwner();

	if(player->GetPos().y != m_dashDest.y) {
		/*if (!((PlayerMovementModule*)m_pController->GetModule(L"MovementModule"))->GetGround()) {
			player->ChangeGravity();
			player->SetPos(m_dashDest);
		}*/
	}
	else {
		player->SetPos(m_dashDest);
	}
}