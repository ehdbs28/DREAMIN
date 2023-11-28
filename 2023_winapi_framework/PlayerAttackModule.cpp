#include "pch.h"
#include "PlayerAttackModule.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "ModuleController.h"
#include "Object.h"
#include "Bullet.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "PlayerMovementModule.h"

PlayerAttackModule::PlayerAttackModule(ModuleController* _controller)
	: BaseModule(_controller)
	, m_pTarget(nullptr)
	, m_fAttackDelayTimer(0.f)
	, m_fAttackDelay(0.1f)
	, m_fDamage(10.f)
	, m_isAttack(false)
{
}

PlayerAttackModule::~PlayerAttackModule()
{
}

void PlayerAttackModule::UpdateModule()
{
	InputSetting();
	if (m_isAttack) {
		m_fAttackDelayTimer += fDT;
		if (m_fAttackDelayTimer >= m_fAttackDelay) {
			m_isAttack = false;
		}
	}
}

void PlayerAttackModule::InputSetting()
{
	if (KEY_PRESS(KEY_TYPE::C)) {
		Attack();
	}

	Vec2 targetPos;
	Vec2 vPos = m_pController->GetOwner()->GetPos();

	if (nullptr == m_pTarget) {
		PlayerMovementModule* movementModule = (PlayerMovementModule*)m_pController->GetModule(L"MovementModule");
		Vec2 frontDir = movementModule->GetFrontDir();
		targetPos = vPos + frontDir;
	}
	else {
		targetPos = m_pTarget->GetPos();
	}

	Vec2 targetDir = (targetPos - vPos).Normalize();

	m_attackDir = targetDir;
	m_attackPoint = vPos + targetDir * 30;
}

void PlayerAttackModule::Attack()
{
	if (m_isAttack) {
		return;
	}

	m_isAttack = true;
	m_fAttackDelayTimer = 0.f;
	CreateBullet();
}

void PlayerAttackModule::CreateBullet()
{
	Bullet* pBullet = new Bullet(OBJECT_GROUP::PLAYER);
	pBullet->SetName(L"PlayerBullet");
	pBullet->SetPos(m_attackPoint);
	pBullet->SetScale(Vec2(25.f, 25.f));
	pBullet->SetDir(m_attackDir);

	SceneMgr::GetInst()->GetCurScene()->AddObject(pBullet, OBJECT_GROUP::BULLET);
}