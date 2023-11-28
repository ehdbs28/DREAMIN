#include "pch.h"
#include "PlayerMovementModule.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "ModuleController.h"
#include "Object.h"

PlayerMovementModule::PlayerMovementModule(ModuleController* _controller)
	: BaseModule(_controller)
	, m_fGravity(2.45f)
	, m_fMovementSpeed(300.f)
	, m_fJumpPower(-850.f)
	, m_inputDir(Vec2(0, 0))
	, m_movementVelocity(Vec2(0, 0))
	, m_verticalVelocity(Vec2(0, 0))
	, m_frontDir(Vec2(1, 0))
	, m_isGround(false)
{
}

PlayerMovementModule::~PlayerMovementModule()
{
}

void PlayerMovementModule::UpdateModule()
{
	SetInputValue();
	CalcMovement();

	Vec2 vPos = m_pController->GetOwner()->GetPos();
	vPos = vPos + m_movementVelocity * fDT;
	m_pController->GetOwner()->SetPos(vPos);
}

void PlayerMovementModule::SetInputValue()
{
	if (KEY_PRESS(KEY_TYPE::LEFT)) {
		m_frontDir.x = -1;
		m_inputDir.x = -1;
	}
	else if (KEY_PRESS(KEY_TYPE::RIGHT)) {
		m_frontDir.x = 1;
		m_inputDir.x = 1;
	}
	else {
		m_inputDir.x = 0;
	}

	if (KEY_DOWN(KEY_TYPE::X)) {
		if (!m_isGround) {
			return;
		}

		m_verticalVelocity.y = m_fJumpPower;
	}
}

void PlayerMovementModule::CalcMovement()
{
	m_movementVelocity = m_inputDir * m_fMovementSpeed;
	m_movementVelocity = m_movementVelocity + m_verticalVelocity;

	if (m_isGround && m_verticalVelocity.y > 0.0f) {
		m_verticalVelocity.y = 0.1f;
	}
	else {
		m_verticalVelocity.y += m_fGravity;
	}
}