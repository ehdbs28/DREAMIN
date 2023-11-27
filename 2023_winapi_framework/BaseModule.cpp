#include "pch.h"
#include "BaseModule.h"
#include "ModuleController.h"

BaseModule::BaseModule(ModuleController* _controller)
	: m_pController(_controller)
{
}

BaseModule::~BaseModule()
{
}
