#pragma once
#include "BaseModule.h"

class Object;

class PlayerAttackModule : public BaseModule
{
public:
	PlayerAttackModule(ModuleController* _controller);
	virtual ~PlayerAttackModule();

public:
	virtual void UpdateModule() override;

private:
	void InputSetting();
	void Attack();

private:
	Object* m_pTarget;

	float m_fAttackDelayTimer;
	float m_fAttackDelay;

	float m_fDamage;

	bool m_isAttack;
};

