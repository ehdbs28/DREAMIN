#include "pch.h"
#include "MovementPattern.h"
#include "ModuleController.h"
#include "Object.h"
#include "TimeMgr.h"
#include "Easing.h"
MovementPattern::MovementPattern(ModuleController* _controlle)
	: BossPattern(_controlle)
	, m_currentTime(0.f)
	, m_percent(0.f)
	, m_index(0)
	, m_movementTimer(0.5f)
{
	Vec2 bossScale = m_pModuleController->GetOwner()->GetScale();
	m_destinations[0] = Vec2(bossScale.x / 2.f + 100.f, 120 + bossScale.y / 2 + 100.f);
	m_destinations[1] = Vec2(WINDOW_WIDTH - (bossScale.x / 2.f + 100.f), 120 + bossScale.y / 2 + 100.f);
	m_destinations[2] = Vec2(bossScale.x / 2.f + 100.f, WINDOW_HEIGHT - (120 + bossScale.y / 2 + 100.f));
	m_destinations[3] = Vec2(WINDOW_WIDTH - (bossScale.x / 2.f + 100.f), WINDOW_HEIGHT - (120 + bossScale.y / 2 + 100.f));
	
	for (int i = 0; i < 4; i++) {
		m_order[i] = i;
	}
}

MovementPattern::~MovementPattern()
{
}

void MovementPattern::ExcutePattern()
{
	m_currentTime += fDT;
	m_percent = m_currentTime / m_movementTimer;
	Vec2 lerp = Vec2::Lerp(m_origin, m_destination, EaseInOutCubic(m_percent));
	m_pModuleController->GetOwner()->SetPos(lerp);

	if (m_percent >= 1.f) {
		m_isExecute = false;
	}
}

void MovementPattern::SetExcute()
{
	m_currentTime = 0.f;
	m_percent = 0.f;
	

	m_origin = m_pModuleController->GetOwner()->GetPos();
	SelectDestination();
	
	BossPattern::SetExcute();
}

void MovementPattern::SelectDestination()
{
	if (m_index >= 4) {
		ShuffleOrder();
	}
	m_destination = m_destinations[m_order[m_index++]];
}

void MovementPattern::ShuffleOrder()
{
	for (int i = 0; i < 4; i++) {
		m_order[i] = i;
	}

	int sour, dest, temp;
	for (int i = 0; i < 100; i++) {
		sour = rand() % 4;
		dest = rand() % 4;

		temp = m_order[sour];
		m_order[sour] = m_order[dest];
		m_order[dest] = temp;
	}

	m_index = 0;
}
