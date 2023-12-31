#pragma once
#include "BaseModule.h"

class PlayerDashModule : public BaseModule
{
public:
	PlayerDashModule(ModuleController* _controller);
	virtual ~PlayerDashModule();

public:
	virtual void EnterModule() override;
	virtual void UpdateModule() override;
	virtual void ExitModule() override;

private:
	void Dash();

private:
	Vec2 m_dashDir;
	float m_dashSpeed;

	float m_dashDuration;
	float m_dashDurationTimer;

};

