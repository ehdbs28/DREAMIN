#include "pch.h"
#include "PlayerMovementModule.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "ModuleController.h"
#include "Object.h"
#include "Rigidbody.h"
#include "PlayerDashModule.h"
#include "Player.h"
#include "Animator.h"

PlayerMovementModule::PlayerMovementModule(ModuleController* _controller)
	: BaseModule(_controller)
	, m_fGravity(2.45f)
	, m_fMovementSpeed(300.f)
	, m_fJumpPower(-1000.f)
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

	if (((PlayerDashModule*)m_pController->GetModule(L"DashModule"))->IsDash()) {
		return;
	}

	Rigidbody* pRigidbody = m_pController->GetOwner()->GetRigidbody();
	pRigidbody->SetVelocity(m_movementVelocity * fDT);
}

void PlayerMovementModule::SetInputValue()
{
	if (KEY_PRESS(KEY_TYPE::LEFT)) {
		m_frontDir.x = -1;
		m_inputDir.x = -1;
		m_pController->GetOwner()->GetAnimator()->PlayAnim(L"Minsung_Walk_Left_Top", true);
	}
	else if (KEY_PRESS(KEY_TYPE::RIGHT)) {
		m_frontDir.x = 1;
		m_inputDir.x = 1;
		m_pController->GetOwner()->GetAnimator()->PlayAnim(L"Minsung_Walk_Right_Top", true);
	}
	else {
		m_inputDir.x = 0;
		if (m_frontDir.x == -1)
		{
			m_pController->GetOwner()->GetAnimator()->PlayAnim(L"Minsung_Idle_Left_Top", true);
		}
		else if(m_frontDir.x == 1)
		{
			m_pController->GetOwner()->GetAnimator()->PlayAnim(L"Minsung_Idle_Right_Top", true);
		}
	}

	if (KEY_DOWN(KEY_TYPE::X)) {
		if (!m_isGround) {
			return;
			m_pController->GetOwner()->GetAnimator()->StopAnim(NULL);
		}
		m_verticalVelocity.y = m_fJumpPower;
		if (m_frontDir.x == -1)
		{
			m_pController->GetOwner()->GetAnimator()->PlayAnim(L"Minsung_Jump_Left_Top", true);
		}
		else if (m_frontDir.x == 1)
		{
			m_pController->GetOwner()->GetAnimator()->PlayAnim(L"Minsung_Jump_Right_Top", true);
		}
	}
}

void PlayerMovementModule::CalcMovement()
{
	m_movementVelocity = m_inputDir * m_fMovementSpeed;
	m_movementVelocity = m_movementVelocity + (m_verticalVelocity * ((Player*)m_pController->GetOwner())->GetGravityDir());

	if (m_isGround && m_verticalVelocity.y > 0.0f) {
		m_verticalVelocity.y = 0.1f;
	}
	else {
		m_verticalVelocity.y += m_fGravity;
	}
}