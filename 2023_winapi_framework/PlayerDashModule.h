#pragma once
#include "BaseModule.h"

class PlayerDashModule : public BaseModule
{
public:
	PlayerDashModule(ModuleController* _controller);
	virtual ~PlayerDashModule();

public:
	virtual void UpdateModule() override;

private:
	void InputSetting();
	void Dash();

public:
	const bool& IsDash() { return m_isDash; }

private:
	Vec2 m_dashDest;

	float m_dashDurationTimer;
	float m_dashDuration;

	bool m_isDash;

};

