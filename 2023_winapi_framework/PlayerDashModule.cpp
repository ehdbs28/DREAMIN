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
{
}

PlayerDashModule::~PlayerDashModule()
{
}

void PlayerDashModule::EnterModule()
{
	BaseModule::EnterModule();
	if (KEY_PRESS(KEY_TYPE::UP)) {
		m_dashDest.y = (float)WINDOW_HEIGHT / 5.f + m_pController->GetOwner()->GetScale().y / 2.f;
	}
	else if (KEY_PRESS(KEY_TYPE::DOWN)) {
		m_dashDest.y = (float)WINDOW_HEIGHT - ((float)WINDOW_HEIGHT / 5.f + m_pController->GetOwner()->GetScale().y / 2.f);
	}
	else if (KEY_PRESS(KEY_TYPE::LEFT)) {
		m_dashDest.x = 0.f + m_pController->GetOwner()->GetScale().x / 2.f;
	}
	else if (KEY_PRESS(KEY_TYPE::RIGHT)) {
		m_dashDest.x = WINDOW_WIDTH - m_pController->GetOwner()->GetScale().x / 2.f;
	}

	Player* player = (Player*)m_pController->GetOwner();

	if (player->GetPos().y != m_dashDest.y) {
		player->ChangeGravity();
		player->SetPos(m_dashDest);
	}
	else {
		player->SetPos(m_dashDest);
	}

	m_pController->ChangeModule(L"IdleModule");
}

void PlayerDashModule::UpdateModule()
{
}

void PlayerDashModule::ExitModule()
{
	BaseModule::ExitModule();
}