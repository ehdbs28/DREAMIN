#include "pch.h"
#include "BossLaserAroundPattern.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Laser.h"
#include "ModuleController.h"
#include "Object.h"
#include "Player.h"
#include "Boss.h"
#include "TimeMgr.h"

BossLaserAroundPattern::BossLaserAroundPattern(ModuleController* _controller)
	: BossPattern(_controller)
	, m_bulletCnt(8)
	, m_angle(0)
	, m_interval(360 / m_bulletCnt)
	, m_generateDelay(0.05f)
	, m_currentTime(0.f)
{
}

BossLaserAroundPattern::~BossLaserAroundPattern()
{
}

void BossLaserAroundPattern::ExcutePattern()
{
	if (m_vecLaser.size() < m_bulletCnt) {
		m_currentTime += fDT;
		if (m_currentTime >= m_generateDelay) {
			float fRadian = m_angle * (M_PI / 180.f);

			Laser* laser = new Laser(1.5f, 1.5f);
			laser->SetName(L"Laser");
			laser->SetScale(Vec2(800, 200));
			Vec2 vPos = m_pModuleController->GetOwner()->GetPos();
			vPos += Vec2(cosf(fRadian), sinf(fRadian)) * 100 - Vec2(15, 0);
			laser->SetPos(vPos);
			laser->SetAngle(m_angle);

			m_vecLaser.push_back(laser);
			SceneMgr::GetInst()->GetCurScene()->AddObject(laser, OBJECT_GROUP::BULLET);
			m_angle += m_interval;
			m_currentTime = 0;
		}
	}
	else {
		bool isEnd = true;
		for (auto& laser : m_vecLaser) {
			if (!laser->GetIsDead()) {
				isEnd = false;
				break;
			}
		}
		m_isExecute = !isEnd;
	}
}

void BossLaserAroundPattern::SetExcute()
{
	m_vecLaser.clear();
	m_angle = 0;
	m_currentTime = 0;
	BossPattern::SetExcute();
}
