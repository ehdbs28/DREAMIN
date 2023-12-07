#include "pch.h"
#include "Boss.h"
#include "ModuleController.h"
#include "Texture.h"
#include "Animator.h"
#include "BossIdleModule.h"
#include "BossPatternModule.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Player.h"
#include "Object.h"
#include "Rigidbody.h"

Boss::Boss()
	: m_pTex(nullptr)
	, m_pModuleController(nullptr)
	, m_pTarget(nullptr)
{
	CreateRigidbody();
	GetRigidbody()->SetGravityScale(0.f);

	m_pModuleController = new ModuleController;
	m_pModuleController->SetOwner(this);

	m_pModuleController->AddModule(L"IdleModule", new BossIdleModule(m_pModuleController));
	m_pModuleController->AddModule(L"PatternModule", new BossPatternModule(m_pModuleController));
	m_pModuleController->ChangeModule(L"IdleModule");

	std::vector<Object*> objs = SceneMgr::GetInst()->GetCurScene()->GetGroupObject(OBJECT_GROUP::PLAYER);
	m_pTarget = (Player*)objs.front();
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
