#include "pch.h"
#include "HorizontalWallPattern.h"
#include "ModuleController.h"
#include "WallAttack.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "Object.h"
#include "TimeMgr.h"
#include "Collider.h"
#include "CameraManager.h"

HorizontalWallPattern::HorizontalWallPattern(ModuleController* _controller)
	: BossPattern(_controller)
	, m_currentTime(0.f)
	, m_rotateTimer(0.5f)
	, m_wallCnt(3)
	, m_interval(0)
	, m_generateDelay(0.1f)
	, m_readyToAttack(false)
	, m_dir(1)
{
	m_interval = (WINDOW_HEIGHT - 120 * 2) / m_wallCnt;
}

HorizontalWallPattern::~HorizontalWallPattern()
{
}

void HorizontalWallPattern::ExcutePattern()
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
				CameraManager::GetInst()->Shake(3, 0.05f);
				WallAttack* wall = new WallAttack(false);
				wall->SetName(L"WallAttack");
				wall->SetScale(Vec2(800, 60));
				wall->GetCollider()->SetScale(Vec2(800, 60));
				wall->SetAngle(90);

				if (m_dir == 1) {
					wall->SetPos(Vec2(WINDOW_WIDTH / 2.f, 120 + (m_vecWalls.size() + 1) * m_interval));
				}
				else if (m_dir == -1)
				{
					wall->SetPos(Vec2(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT - (120 + (m_vecWalls.size() + 1) * m_interval)));
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

void HorizontalWallPattern::SetExcute()
{
	m_currentTime = 0.f;
	m_readyToAttack = false;

	if (rand() % 2 == 1) {
		m_dir *= -1;
	}

	m_vecWalls.clear();
	BossPattern::SetExcute();
}
