#include "pch.h"
#include "BaseModule.h"
#include "ModuleController.h"

BaseModule::BaseModule(ModuleController* _controller)
	: m_pController(_controller)
	, m_active(false)
{
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
