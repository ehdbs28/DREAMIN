#include "pch.h"
#include "BaseModule.h"
#include "ModuleController.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Object.h"
#include "Player.h"

BaseModule::BaseModule(ModuleController* _controller)
	: m_pController(_controller)
	, m_active(false)
	, m_pRigidbody(nullptr)
	, m_pAnimator(nullptr)
	, m_animationKey(L"")
{
	m_pRigidbody = m_pController->GetOwner()->GetRigidbody();
	m_pAnimator = m_pController->GetOwner()->GetAnimator();
}

BaseModule::~BaseModule()
{
}

void BaseModule::EnterModule()
{
	m_active = true;
}

void BaseModule::UpdateModule() {
	if (m_animationKey != L"") {
		int front = m_pController->GetOwner()->GetFrontDir();
		int gravity = m_pRigidbody->GetGravityScale();
		((Player*)m_pController->GetOwner())->SetAnimation(
			m_animationKey,
			false,
			front == 1,
			gravity == 1
		);
	}
}

void BaseModule::ExitModule()
{
	m_active = false;
	m_pAnimator->StopAnim();
}

void BaseModule::SetAnimationKey(wstring _key)
{
	if (_key == L"") {
		return;
	}

	m_animationKey = _key;
}
