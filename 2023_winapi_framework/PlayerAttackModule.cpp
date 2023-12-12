#include "pch.h"
#include "PlayerAttackModule.h"
#include "TimeMgr.h"
#include "ModuleController.h"
#include "Object.h"
#include "KeyMgr.h"
#include "Bullet.h"
#include "Player.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Boss.h"
#include "Animator.h"
#include "Rigidbody.h"
#include "Particle.h"
#include "UIManager.h"
#include "UIPanel.h"
#include "TutScreen.h"

PlayerAttackModule::PlayerAttackModule(ModuleController* _controller)
	: BaseModule(_controller)
	, m_fAttackDelayTimer(0.f)
	, m_fAttackDelay(0.075f)
	, m_damage(1)
{
	SetAnimationKey(L"Minsung_Shoot");
}

PlayerAttackModule::~PlayerAttackModule()
{
}

void PlayerAttackModule::EnterModule()
{
	BaseModule::EnterModule();
	auto tutScreen = std::dynamic_pointer_cast<TutScreen>(UIManager::GetInst()->GetTopPanel());
	if (tutScreen != nullptr) {
		tutScreen->ShotTutClear();
	}
	Shot();
}

void PlayerAttackModule::UpdateModule()
{
	BaseModule::UpdateModule();
	m_fAttackDelayTimer += fDT;
	if (m_fAttackDelayTimer >= m_fAttackDelay) {
		m_pController->ChangeModule(L"IdleModule");
		return;
	}
}

void PlayerAttackModule::ExitModule()
{
	BaseModule::ExitModule();
}

void PlayerAttackModule::Shot()
{
	m_fAttackDelayTimer = 0.f;

	Player* pPlayer = (Player*)m_pController->GetOwner();
	const Boss* pTarget = pPlayer->GetTarget();
	Vec2 targetPos;

	if (pTarget == nullptr) {
		Vec2 vPos = pPlayer->GetPos();
		targetPos = vPos + Vec2(pPlayer->GetFrontDir(), 0);
	}
	else {
		targetPos = pTarget->GetPos();
	}

	Vec2 vPos = m_pController->GetOwner()->GetPos();
	Vec2 targetDir = (targetPos - vPos).Normalize();
	Vec2 attackPoint = vPos + targetDir * 10.f;
	
	if (m_pRigidbody->GetGravityScale() == -1) {
		attackPoint.y += 30;
	}

	m_pController->GetOwner()->SetFront(targetDir.x >= 0 ? 1 : -1);

	Bullet* pBullet = new Bullet(OBJECT_GROUP::PLAYER);
	pBullet->SetName(L"Bullet_Player");
	pBullet->SetPos(attackPoint);
	pBullet->SetScale(Vec2(90.f, 90.f));
	pBullet->SetDamage(m_damage);
	pBullet->SetDir(targetDir);

	Particle* particle = new Particle(PARTICLE_TYPE::PLAYER_SHOOT, 0.01f, false);
	particle->SetPos(attackPoint);
	particle->SetScale(Vec2(60, 60));
	SceneMgr::GetInst()->GetCurScene()->AddObject(particle, OBJECT_GROUP::PARTICLE);

	SceneMgr::GetInst()->GetCurScene()->AddObject(pBullet, OBJECT_GROUP::BULLET);
}