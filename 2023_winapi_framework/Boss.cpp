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
#include "Collider.h"
#include "Game_Scene.h"
#include "DamageCaster.h"
#include "Particle.h"
#include "InGameScreen.h"
#include "UIManager.h"
#include "Animation.h"
#include "ResMgr.h"

Boss::Boss()
	: m_pTex(nullptr)
	, m_pModuleController(nullptr)
	, m_pTarget(nullptr)
{
	CreateRigidbody();
	GetRigidbody()->SetGravityScale(0.f);

	CreateCollider();
	GetCollider()->SetScale(Vec2(120.f, 120.f));

	CreateDamageCaster();
	GetDamageCaster()->SetMaxHealth(300);

	m_pModuleController = new ModuleController;
	m_pModuleController->SetOwner(this);

	m_pModuleController->AddModule(L"IdleModule", new BossIdleModule(m_pModuleController));
	m_pModuleController->AddModule(L"PatternModule", new BossPatternModule(m_pModuleController));
	m_pModuleController->ChangeModule(L"IdleModule");
	ResMgr::GetInst()->LoadSound(L"Explosion", L"Sound\\Explosion.wav", false);
	ResMgr::GetInst()->LoadSound(L"LaserReady", L"Sound\\LaserReady.wav", false);
	ResMgr::GetInst()->LoadSound(L"LaserShoot1", L"Sound\\LaserShoot1.wav", false);
	ResMgr::GetInst()->LoadSound(L"LaserShoot2", L"Sound\\LaserShoot2.wav", false);


	std::vector<Object*> objs = SceneMgr::GetInst()->GetCurScene()->GetGroupObject(OBJECT_GROUP::PLAYER);
	m_pTarget = (Player*)objs.front();
	m_pTarget->SetTarget(this);
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

	Animation* pCurAnim = GetAnimator()->GetCurAnim();
	if (pCurAnim->GetName() == L"Damaged") {
		if (pCurAnim->GetCurFrame() + 1 == pCurAnim->GetMaxFrame()) {
			GetAnimator()->PlayAnim(L"Idle", false);
		}
	}
}

void Boss::OnDamage(float _damage)
{
	GetDamageCaster()->OnDamage(_damage);

	GetAnimator()->PlayAnim(L"Damaged", false);

	float maxHealth = GetDamageCaster()->GetMaxHealth();
	float curHealth = GetDamageCaster()->GetHealth();
	std::dynamic_pointer_cast<InGameScreen>(UIManager::GetInst()->GetTopPanel())->SetBossHpPercent(curHealth / maxHealth);
}

void Boss::DeadHandle()
{
	Particle* particle = new Particle(PARTICLE_TYPE::BOSS_DEAD, 0.06f, false);
	particle->SetPos(GetPos());
	particle->SetScale(Vec2(155, 155));
	SceneMgr::GetInst()->GetCurScene()->AddObject(particle, OBJECT_GROUP::PARTICLE);
	std::dynamic_pointer_cast<Game_Scene>(SceneMgr::GetInst()->GetCurScene())->SetClear();
}
