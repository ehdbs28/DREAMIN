#include "pch.h"
#include "ModuleController.h"
#include "BaseModule.h"

ModuleController::ModuleController()
{
}

ModuleController::~ModuleController()
{
}

void ModuleController::Update()
{
	for (auto& module : m_vecModule) {
		module->UpdateModule();
	}
}

void ModuleController::AddModule(BaseModule* _module)
{
	m_vecModule.push_back(_module);
}
