#include "pch.h"
#include "Boss.h"
#include "ModuleController.h"
#include "Texture.h"
#include "Animator.h"
#include "BossPatternModule.h"

Boss::Boss()
	: m_pTex(nullptr)
	, m_pModuleController(nullptr)
{
	CreateRigidbody();
	m_pModuleController = new ModuleController;
	m_pModuleController->AddModule(L"PatternModule", new BossPatternModule(m_pModuleController));
}

Boss::~Boss()
{
	if (nullptr != m_pModuleController)
		delete m_pModuleController;
}

void Boss::Update()
{
	m_pModuleController->Update();
	GetAnimator()->Update();
}

void Boss::Render(HDC _dc)
{
	Component_Render(_dc);
}
