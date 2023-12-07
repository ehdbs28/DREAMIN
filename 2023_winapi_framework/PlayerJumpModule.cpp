#include "pch.h"
#include "PlayerJumpModule.h"
#include "Rigidbody.h"
#include "ModuleController.h"
#include "Object.h"
#include "TimeMgr.h"
#include "Animator.h"


PlayerJumpModule::PlayerJumpModule(ModuleController* _controller)
	: PlayerAirModule(_controller)
	, m_fJumpPower(-540.f)
{
}

PlayerJumpModule::~PlayerJumpModule()
{
}

void PlayerJumpModule::EnterModule()
{
	m_pRigidbody->SetVelocity(Vec2(0.f, m_fJumpPower * m_pRigidbody->GetGravityScale()));
	int gravity = m_pRigidbody->GetGravityScale();
	// 1이면 바닥에 있는거고 -1이면 천장에 있는거
	m_pAnimator->PlayAnim(L"Minsung_Jump_Right_Top", false);
	BaseModule::EnterModule();
}

void PlayerJumpModule::UpdateModule()
{
	if (m_pRigidbody->GetVelocity().y >= 0.f) {
		m_pController->ChangeModule(L"FallModule");
		return;
	}
	PlayerAirModule::UpdateModule();
}

void PlayerJumpModule::ExitModule()
{
	BaseModule::ExitModule();
}
