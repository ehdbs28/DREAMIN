#pragma once
#include "BaseModule.h"

class Object;

class PlayerAttackModule : public BaseModule
{
public:
	PlayerAttackModule(ModuleController* _controller);
	virtual ~PlayerAttackModule();

public:
	virtual void EnterModule() override;
	virtual void UpdateModule() override;
	virtual void ExitModule() override;

private:
	void Shot();

private:
	float m_fAttackDelayTimer;
	float m_fAttackDelay;

	float m_fDamage;
};

