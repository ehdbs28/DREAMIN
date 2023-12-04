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

	Rigidbody* rigid = m_pController->GetOwner()->GetRigidbody();
	rigid->SetVelocity(m_inputDir * m_fMovementSpeed * fDT);
}