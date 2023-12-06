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

PlayerAttackModule::PlayerAttackModule(ModuleController* _controller)
	: BaseModule(_controller)
	, m_fAttackDelayTimer(0.f)
	, m_fAttackDelay(0.1f)
	, m_fDamage(10.f)
{
}

PlayerAttackModule::~PlayerAttackModule()
{
}

void PlayerAttackModule::EnterModule()
{
	Shot();
	m_fAttackDelayTimer = 0.f;
	BaseModule::EnterModule();
}

void PlayerAttackModule::UpdateModule()
{
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
	//Vec2 targetPos = ((Player*)m_pController->GetOwner())->GetTarget()->GetPos();
	Vec2 targetPos = KeyMgr::GetInst()->GetMousePos();
	Vec2 vPos = m_pController->GetOwner()->GetPos();
	Vec2 targetDir = (targetPos - vPos).Normalize();
	Vec2 attackPoint = vPos + targetDir * 30;

	Bullet* pBullet = new Bullet(OBJECT_GROUP::PLAYER);
	pBullet->SetName(L"PlayerBullet");
	pBullet->SetPos(attackPoint);
	pBullet->SetScale(Vec2(30.f, 30.f));
	pBullet->SetDir(targetDir);

	SceneMgr::GetInst()->GetCurScene()->AddObject(pBullet, OBJECT_GROUP::BULLET);
}