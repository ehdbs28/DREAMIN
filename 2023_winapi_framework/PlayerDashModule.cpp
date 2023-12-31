#include "pch.h"
#include "PlayerDashModule.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "ModuleController.h"
#include "Object.h"
#include "Rigidbody.h"
#include "Player.h"
#include "PlayerMovementModule.h"
#include "Animator.h"
#include "ResMgr.h"
#include "UIManager.h"
#include "TutScreen.h"
#include "CameraManager.h"

PlayerDashModule::PlayerDashModule(ModuleController* _controller)
	: BaseModule(_controller)
	, m_dashDir(Vec2(0.f, 0.f))
	, m_dashSpeed(5000.f)
	, m_dashDuration(0.2f)
	, m_dashDurationTimer(0.f)
{
	SetAnimationKey(L"Minsung_Dash");
}

PlayerDashModule::~PlayerDashModule()
{
}

void PlayerDashModule::EnterModule()
{
	BaseModule::EnterModule();
	ResMgr::GetInst()->Volume(SOUND_CHANNEL::EFFECT, 1.0f);
	auto tutScreen = std::dynamic_pointer_cast<TutScreen>(UIManager::GetInst()->GetTopPanel());
	if (tutScreen != nullptr) {
		tutScreen->DashTutClear();
	}
	Dash();
}

void PlayerDashModule::Dash()
{
	((Player*)m_pController->GetOwner())->SetInvincibility(true);

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

	if (m_dashDir.x != 0) {
		CameraManager::GetInst()->Shake(5, 0.025);
		ResMgr::GetInst()->Play(L"DashSound");
		m_pController->GetOwner()->SetFront(m_dashDir.x);
	}

	if (m_dashDir.y != 0 && m_pRigidbody->GetGravityScale() != m_dashDir.y) {
		CameraManager::GetInst()->Shake(5, 0.025);
		ResMgr::GetInst()->Play(L"DashSound");
		m_pRigidbody->SetGravityScale(m_dashDir.y);
	}

	m_pRigidbody->SetVelocity(m_dashDir * m_dashSpeed);
}

void PlayerDashModule::UpdateModule()
{
	BaseModule::UpdateModule();
	m_dashDurationTimer += fDT;
	if (m_dashDurationTimer >= m_dashDuration) {
		m_pController->ChangeModule(L"IdleModule");
		return;
	}
}

void PlayerDashModule::ExitModule()
{
	((Player*)m_pController->GetOwner())->SetInvincibility(false);
	BaseModule::ExitModule();
}