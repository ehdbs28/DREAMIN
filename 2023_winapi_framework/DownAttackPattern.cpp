#include "pch.h"
#include "DownAttackPattern.h"
#include "ModuleController.h"
#include "Boss.h"
#include "Player.h"
#include "TimeMgr.h"

DownAttackPattern::DownAttackPattern(ModuleController* _controller)
	: BossPattern(_controller)
	, m_originPos(Vec2(0, 0))
	, m_destination(Vec2(0, 0))
	, m_currentTime(0)
	, m_movementTimer(0.5f)
	, m_downTimer(0.25f)
	, m_readyToAttack(false)
{
}

DownAttackPattern::~DownAttackPattern()
{
}

void DownAttackPattern::ExcutePattern()
{
	if (!m_readyToAttack) {
		m_currentTime += fDT;
		float percent = m_currentTime / m_movementTimer;
		//Vec2 lerp= Lerp(m_originPos, m_destination, EaseInOutCubic(percent));
		Vec2 lerp = Vec2::Lerp(m_originPos, m_destination, EaseInOutCubic(percent));
		m_pModuleController->GetOwner()->SetPos(lerp);

		if (percent >= 1.f) {
			m_readyToAttack = true;
			m_originPos = m_destination;
			m_destination.y = WINDOW_HEIGHT - WINDOW_HEIGHT / 5 - m_pModuleController->GetOwner()->GetScale().y / 2;
			m_currentTime = 0.f;
		}
	}
	else {
		m_currentTime += fDT;
		float percent = m_currentTime / m_downTimer;
		Vec2 lerp = Vec2::Lerp(m_originPos, m_destination, EaseInBack(percent));
		m_pModuleController->GetOwner()->SetPos(lerp);

		if (percent >= 1.f) {
			m_isExecute = false;
		}
	}
}

void DownAttackPattern::SetExcute()
{
	m_readyToAttack = false;
	m_currentTime = 0.f;
	
	const Player* pTarget = ((Boss*)m_pModuleController->GetOwner())->GetTarget();
	m_originPos = m_pModuleController->GetOwner()->GetPos();
	m_destination = Vec2(pTarget->GetPos().x, m_originPos.y);

	BossPattern::SetExcute();
}
