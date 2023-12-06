#include "pch.h"
#include "LaserPattern.h"
#include "BossPattern.h"
#include "Bullet.h"
#include "Object.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Boss.h"
#include "ModuleController.h"
#include "Player.h"

LaserPattern::LaserPattern(ModuleController* _controller)
	: BossPattern(_controller)
{
}

LaserPattern::~LaserPattern()
{
}

void LaserPattern::ExcutePattern()
{
	Boss* pBoss = (Boss*)m_pModuleController->GetOwner();
	Vec2 playerPos = pBoss->GetTarget()->GetPos();
}

void LaserPattern::CreateBullet()
{
	// prefab을 만든거야
	Bullet* pBullet = new Bullet(OBJECT_GROUP::MONSTER);
	pBullet->SetName(L"MonsterLaser");
	pBullet->SetPos(m_attackPoint);
	pBullet->SetScale(Vec2(25.f, 25.f));
	pBullet->SetDir(m_attackDir);

	// instantiate
	SceneMgr::GetInst()->GetCurScene()->AddObject(pBullet, OBJECT_GROUP::BULLET);
}