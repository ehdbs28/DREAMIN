#include "pch.h"
#include "LaserPattern.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Laser.h"

LaserPattern::LaserPattern(ModuleController* _controller)
	: BossPattern(_controller)
{
}

LaserPattern::~LaserPattern()
{
}

void LaserPattern::ExcutePattern()
{
	m_isExecute = true;
	Laser* laser = new Laser;
	laser->SetScale(Vec2(500, 100));
	laser->SetPos(Vec2(70, 300));
	laser->SetName(L"Laser");
	laser->SetAngle(60);
	SceneMgr::GetInst()->GetCurScene()->AddObject(laser, OBJECT_GROUP::MONSTER);
	m_isExecute = false;
}
