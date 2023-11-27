#include "pch.h"
#include "PlayerMovementModule.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "ModuleController.h"
#include "Object.h"

PlayerMovementModule::PlayerMovementModule(ModuleController* _controller)
	: BaseModule(_controller)
	, m_fGravity(4.9f)
	, m_fMovementSpeed(10.f)
	, m_fJumpPower(-10.f)
	, m_inputDir(Vec2(0, 0))
	, m_movementVelocity(Vec2(0, 0))
	, m_verticalVelocity(Vec2(0, 0))
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
	if (KEY_PRESS(KEY_TYPE::A)) {
		m_inputDir.x = -1;
	}
	else if (KEY_PRESS(KEY_TYPE::D)) {
		m_inputDir.x = 1;
	}
	else {
		m_inputDir.x = 0;
	}

	if (KEY_DOWN(KEY_TYPE::SPACE)) {
		m_verticalVelocity.y = m_fJumpPower;
	}
}

void PlayerMovementModule::CalcMovement()
{
	m_movementVelocity = m_inputDir * m_fMovementSpeed;
	m_movementVelocity = m_movementVelocity + m_verticalVelocity;

	if (m_isGround && m_verticalVelocity.y < 0.0f) {
		m_verticalVelocity.y = -1.0f;
	}
	else {
		m_verticalVelocity.y += m_fGravity;
	}
}