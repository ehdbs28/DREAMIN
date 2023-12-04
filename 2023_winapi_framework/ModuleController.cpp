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
	if (m_currentModule != nullptr) {
		m_currentModule->UpdateModule();
	}
}

void ModuleController::AddModule(wstring _key, BaseModule* _module)
{
	m_moduleMap.insert({ _key, _module });
}

void ModuleController::ChangeModule(wstring _key)
{
	if (m_currentModule != nullptr) {
		m_currentModule->ExitModule();
	}
	m_currentModule = m_moduleMap[_key];
	m_currentModule->EnterModule();
}
