#include "pch.h"
#include "BaseModule.h"
#include "ModuleController.h"
#include "Rigidbody.h"
#include "Animator.h"
#include "Object.h"

BaseModule::BaseModule(ModuleController* _controller)
	: m_pController(_controller)
	, m_active(false)
	, m_pRigidbody(nullptr)
	, m_pAnimator(nullptr)
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

void BaseModule::ExitModule()
{
	m_active = false;
}
