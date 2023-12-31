#include "pch.h"
#include "LaserPattern.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Laser.h"
#include "ModuleController.h"
#include "Object.h"
#include "Player.h"
#include "Boss.h"
#include "TimeMgr.h"
#include "ResMgr.h"

LaserPattern::LaserPattern(ModuleController* _controller)
	: BossPattern(_controller)
	, m_bulletCnt(5)
	, m_angle(0)
	, m_interval(360 / m_bulletCnt)
	, m_generateDelay(0.05f)
	, m_currentTime(0.f)
	, m_targetAngle(0)
{
}

LaserPattern::~LaserPattern()
{
}

void LaserPattern::ExcutePattern()
{
	if (m_vecLaser.size() < m_bulletCnt) {
		m_currentTime += fDT;
		if (m_currentTime >= m_generateDelay) {
			float fRadian = m_angle * (M_PI / 180.f);

			Laser* laser = new Laser(0.8f, 0.8f);
			laser->SetName(L"Laser");
			laser->SetScale(Vec2(800, 200));
			Vec2 vPos = m_pModuleController->GetOwner()->GetPos();
			vPos += Vec2(cosf(fRadian), sinf(fRadian)) * 100;
			laser->SetPos(vPos);
			laser->SetAngle(m_targetAngle);

			ResMgr::GetInst()->Play(L"LaserReady");

			m_vecLaser.push_back(laser);
			SceneMgr::GetInst()->GetCurScene()->AddObject(laser, OBJECT_GROUP::BOSS_ATTACK);
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

void LaserPattern::SetExcute()
{
	const Player* pTarget = ((Boss*)m_pModuleController->GetOwner())->GetTarget();
	Vec2 vPos = m_pModuleController->GetOwner()->GetPos();
	Vec2 targetPos = pTarget->GetPos();
	Vec2 targetDir = (targetPos - vPos).Normalized();
	m_targetAngle = atan2(targetDir.y, targetDir.x) * (180.f / M_PI);

	m_vecLaser.clear();
	m_angle = 0;
	m_currentTime = 0;
	BossPattern::SetExcute();
}
