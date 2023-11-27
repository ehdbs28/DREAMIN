#include "pch.h"
#include "ModuleController.h"
#include "BaseModule.h"

ModuleController::ModuleController()
	: m_pOwner(nullptr)
{
}

ModuleController::~ModuleController()
{
	for (auto& pair : m_moduleMap) {
		delete pair.second;
	}
	m_moduleMap.clear();
}

void ModuleController::Update()
{
	for (auto& pair : m_moduleMap) {
		pair.second->UpdateModule();
	}
}

void ModuleController::AddModule(wstring _key, BaseModule* _module)
{
	m_moduleMap.insert({ _key, _module });
}
