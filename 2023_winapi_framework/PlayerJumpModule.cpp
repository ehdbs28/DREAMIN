#include "pch.h"
#include "PlayerJumpModule.h"
#include "Rigidbody.h"
#include "ModuleController.h"
#include "Object.h"
#include "TimeMgr.h"
#include "Animator.h"
#include "Player.h"
#include "ResMgr.h"
#include "UIManager.h"
#include "TutScreen.h"

PlayerJumpModule::PlayerJumpModule(ModuleController* _controller)
	: PlayerAirModule(_controller)
	, m_fJumpPower(-540.f)
{
	SetAnimationKey(L"Minsung_Jump");
}

PlayerJumpModule::~PlayerJumpModule()
{
}

void PlayerJumpModule::EnterModule()
{
	BaseModule::EnterModule();
	auto tutScreen = std::dynamic_pointer_cast<TutScreen>(UIManager::GetInst()->GetTopPanel());
	if (tutScreen != nullptr) {
		tutScreen->JumpTutClear();
	}
	m_pRigidbody->SetVelocity(Vec2(0.f, m_fJumpPower * m_pRigidbody->GetGravityScale()));
	ResMgr::GetInst()->Volume(SOUND_CHANNEL::EFFECT, 1.0f);
	ResMgr::GetInst()->Play(L"JumpSound");
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
