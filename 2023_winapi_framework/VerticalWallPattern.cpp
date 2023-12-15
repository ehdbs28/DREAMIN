#include "pch.h"
#include "VerticalWallPattern.h"
#include "ModuleController.h"
#include "WallAttack.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Object.h"
#include "TimeMgr.h"
#include "Collider.h"

VerticalWallPattern::VerticalWallPattern(ModuleController* _controller)
	: BossPattern(_controller)
	, m_currentTime(0.f)
	, m_rotateTimer(0.5f)
	, m_wallCnt(5)
	, m_interval(0)
	, m_generateDelay(0.1f)
	, m_readyToAttack(false)
	, m_dir(1)
{
	m_interval = WINDOW_WIDTH / m_wallCnt;
}

VerticalWallPattern::~VerticalWallPattern()
{
}

void VerticalWallPattern::ExcutePattern()
{
	if (!m_readyToAttack) {
		m_currentTime += fDT;
		float percent = EaseOutCubic(m_currentTime / m_rotateTimer);
		float angle = 360 * m_dir * percent;
		m_pModuleController->GetOwner()->SetAngle(angle);
		if (percent >= 1) {
			m_readyToAttack = true;
			m_currentTime = 0.f;
		}
	}
	else {
		if (m_vecWalls.size() < m_wallCnt) {
			m_currentTime += fDT;
			if (m_currentTime >= m_generateDelay) {
				WallAttack* wall = new WallAttack;
				wall->SetName(L"WallAttack");
				wall->SetScale(Vec2(75, 360));
				wall->GetCollider()->SetScale(Vec2(75, 360));

				if (m_dir == 1) {
					wall->SetPos(Vec2((m_vecWalls.size() + 1) * m_interval, WINDOW_HEIGHT / 2));
				}
				else if(m_dir == -1)
				{
					wall->SetPos(Vec2(WINDOW_WIDTH - ( (m_vecWalls.size() + 1) * m_interval), WINDOW_HEIGHT / 2));
				}

				m_vecWalls.push_back(wall);
				SceneMgr::GetInst()->GetCurScene()->AddObject(wall, OBJECT_GROUP::BOSS_ATTACK);
				m_currentTime = 0.f;
			}
		}
		else {
			bool isEnd = true;
			for (auto& wall : m_vecWalls) {
				if (!wall->GetIsDead()) {
					isEnd = false;
					break;
				}
			}
			m_isExecute = !isEnd;
		}
	}
}

void VerticalWallPattern::SetExcute()
{
	m_currentTime = 0.f;
	m_readyToAttack = false;

	if (rand() % 2 == 1) {
		m_dir *= -1;
	}

	m_vecWalls.clear();
	BossPattern::SetExcute();
}
