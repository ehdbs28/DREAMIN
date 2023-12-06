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
	Vec2 m_dashDest;

};

