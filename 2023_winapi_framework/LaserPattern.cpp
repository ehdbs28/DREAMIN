#include "pch.h"
#include "LaserPattern.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Laser.h"
#include "ModuleController.h"
#include "Object.h"

LaserPattern::LaserPattern(ModuleController* _controller)
	: BossPattern(_controller)
	, m_bulletCnt(1)
	, m_angle(0)
	, m_interval(30)
{
}

LaserPattern::~LaserPattern()
{
}

void LaserPattern::ExcutePattern()
{
	if (m_vecLaser.size() < m_bulletCnt) {

		float fRadian = m_angle * (M_PI / 180.f);

		Laser* laser = new Laser(1.5f, 1.5f);
		laser->SetName(L"Laser");
		laser->SetScale(Vec2(800, 100));
		Vec2 vPos = m_pModuleController->GetOwner()->GetPos();
		vPos += Vec2(cosf(fRadian), sinf(fRadian)) * 100.f;
		laser->SetPos(Vec2(300, 300));
		laser->SetAngle(0);

		m_vecLaser.push_back(laser);
		SceneMgr::GetInst()->GetCurScene()->AddObject(laser, OBJECT_GROUP::MONSTER);
		m_angle += m_interval;
	}

	//if (m_pLaser->GetIsDead()) {
	//	m_pLaser = nullptr;
	//	m_isExecute = false;
	//}
}

void LaserPattern::SetExcute()
{
	BossPattern::SetExcute();
	m_vecLaser.clear();
	m_angle = 0;
}
