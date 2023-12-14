#include "pch.h"
#include "LaserPattern.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Laser.h"

LaserPattern::LaserPattern(ModuleController* _controller)
	: BossPattern(_controller)
	, m_pLaser(nullptr)
{
}

LaserPattern::~LaserPattern()
{
}

void LaserPattern::ExcutePattern()
{
	if (m_pLaser == nullptr) {
		m_pLaser = new Laser(1.5f, 1.5f);
		m_pLaser->SetScale(Vec2(500, 100));
		m_pLaser->SetPos(Vec2(70, 300));
		m_pLaser->SetName(L"Laser");
		//laser->SetAngle(30);
		SceneMgr::GetInst()->GetCurScene()->AddObject(m_pLaser, OBJECT_GROUP::MONSTER);
	}

	if (m_pLaser->GetIsDead()) {
		m_pLaser = nullptr;
		m_isExecute = false;
	}
}
