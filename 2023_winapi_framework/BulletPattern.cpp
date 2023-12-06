#include "pch.h"
#include "BulletPattern.h"
#include "BossPattern.h"
#include "Bullet.h"
#include "Object.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Boss.h"
#include "ModuleController.h"
#include "Player.h"

BulletPattern::BulletPattern(ModuleController* _controller)
	:BossPattern(_controller)
{

}

BulletPattern::~BulletPattern()
{

}

void BulletPattern::ExcutePattern()
{
	Bullet* pBullet = new Bullet(OBJECT_GROUP::MONSTER);
	pBullet->SetName(L"MonsterBullet");
	pBullet->SetPos(m_attackPoint);
	pBullet->SetScale(Vec2(25.f, 25.f));
	pBullet->SetDir(m_attackDir);

	SceneMgr::GetInst()->GetCurScene()->AddObject(pBullet, OBJECT_GROUP::BULLET);
}