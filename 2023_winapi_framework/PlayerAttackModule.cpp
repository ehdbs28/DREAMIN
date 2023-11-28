#include "pch.h"
#include "PlayerAttackModule.h"
#include "KeyMgr.h"
#include "TimeMgr.h"

PlayerAttackModule::PlayerAttackModule(ModuleController* _controller)
	: BaseModule(_controller)
	, m_pTarget(nullptr)
	, m_fAttackDelayTimer(0.f)
	, m_fAttackDelay(0.1f)
	, m_fDamage(10.f)
	, m_isAttack(false)
{
}

PlayerAttackModule::~PlayerAttackModule()
{
}

void PlayerAttackModule::UpdateModule()
{
	InputSetting();
	if (m_isAttack) {
		m_fAttackDelayTimer += fDT;
		if (m_fAttackDelayTimer >= m_fAttackDelay) {
			m_isAttack = false;
		}
	}
}

void PlayerAttackModule::InputSetting()
{
	if (KEY_PRESS(KEY_TYPE::C)) {
		Attack();
	}
}

void PlayerAttackModule::Attack()
{
	if (m_isAttack) {
		return;
	}

	m_isAttack = true;
	m_fAttackDelayTimer = 0.f;

	// 총알 생성 들어가야 함
}
