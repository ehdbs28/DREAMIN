#include "pch.h"
#include "DownAttackPattern.h"
#include "ModuleController.h"
#include "Boss.h"
#include "Player.h"
#include "TimeMgr.h"
#include "WallAttack.h"
#include "SceneMgr.h"
#include "Scene.h"
#include "CameraManager.h"

DownAttackPattern::DownAttackPattern(ModuleController* _controller)
	: BossPattern(_controller)
	, m_originPos(Vec2(0, 0))
	, m_destination(Vec2(0, 0))
	, m_currentTime(0)
	, m_movementTimer(0.5f)
	, m_downTimer(0.05f)
	, m_readyToAttack(false)
	, m_arrived(false)
	, m_isEnd(false)
	, m_generateDelay(0.1f)
	, m_interval(100)
	, m_wallCnt(4)
{
}

DownAttackPattern::~DownAttackPattern()
{
}

void DownAttackPattern::ExcutePattern()
{
	if (!m_arrived) {
		m_currentTime += fDT;
		float percent = m_currentTime / m_movementTimer;
		Vec2 lerp = Vec2::Lerp(m_originPos, m_destination, EaseInOutCubic(percent));
		m_pModuleController->GetOwner()->SetPos(lerp);

		if (percent >= 1.f) {
			m_arrived = true;
			m_originPos = m_destination;
			m_destination.y = WINDOW_HEIGHT - WINDOW_HEIGHT / 5 - m_pModuleController->GetOwner()->GetScale().y / 2;
			m_currentTime = 0.f;
		}
	}
	else {
		if (m_readyToAttack) {
			if (m_vecWalls.size() < m_wallCnt * 2) {
				m_currentTime += fDT;
				if (m_currentTime >= m_generateDelay) {
					Vec2 vPos = m_pModuleController->GetOwner()->GetPos();

					WallAttack* wall1 = new WallAttack;
					wall1->SetName(L"WallAttack");
					wall1->SetScale(Vec2(100, 360));
					wall1->SetPos(Vec2(vPos.x + m_interval * (m_vecWalls.size() / 2.f), WINDOW_HEIGHT / 2.f));

					WallAttack* wall2 = new WallAttack;
					wall2->SetName(L"WallAttack");
					wall2->SetScale(Vec2(100, 360));
					wall2->SetPos(Vec2(vPos.x - m_interval * (m_vecWalls.size() / 2.f), WINDOW_HEIGHT / 2.f));

					m_vecWalls.push_back(wall1);
					m_vecWalls.push_back(wall2);
					SceneMgr::GetInst()->GetCurScene()->AddObject(wall1, OBJECT_GROUP::BOSS_ATTACK);
					SceneMgr::GetInst()->GetCurScene()->AddObject(wall2, OBJECT_GROUP::BOSS_ATTACK);
					m_currentTime = 0.f;
				}
			}
			else {
				if (!m_isEnd) {
					m_isEnd = true;
					for (auto& wall : m_vecWalls) {
						if (!wall->GetIsDead()) {
							m_isEnd = false;
							break;
						}
					}
					m_currentTime = 0.f;
				}
				else {
					m_currentTime += fDT;
					float percent = m_currentTime / m_movementTimer;
					Vec2 lerp = Vec2::Lerp(m_destination, m_originPos, EaseInOutCubic(percent));
					m_pModuleController->GetOwner()->SetPos(lerp);

					if (percent >= 1.f) {
						m_isExecute = false;
					}
				}
			}
		}
		else {
			m_currentTime += fDT;
			float percent = m_currentTime / m_downTimer;
			Vec2 lerp = Vec2::Lerp(m_originPos, m_destination, EaseInBack(percent));
			m_pModuleController->GetOwner()->SetPos(lerp);

			if (percent >= 1.f) {
				CameraManager::GetInst()->Shake(50, 0.1f);
				m_readyToAttack = true;
				m_currentTime = 0.f;
			}
		}
	}
}

void DownAttackPattern::SetExcute()
{
	m_readyToAttack = false;
	m_arrived = false;
	m_isEnd = false;
	m_currentTime = 0.f;
	
	const Player* pTarget = ((Boss*)m_pModuleController->GetOwner())->GetTarget();
	m_originPos = m_pModuleController->GetOwner()->GetPos();
	m_destination = Vec2(pTarget->GetPos().x, m_originPos.y);

	m_vecWalls.clear();

	BossPattern::SetExcute();
}
