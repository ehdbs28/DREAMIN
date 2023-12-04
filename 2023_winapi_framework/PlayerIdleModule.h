#pragma once
#include "BaseModule.h"

class PlayerIdleModule :
    public BaseModule
{
public:
	PlayerIdleModule(ModuleController* _controller);
	virtual ~PlayerIdleModule() override;

public:
	virtual void EnterModule() override;
	virtual void UpdateModule() override;
	virtual void ExitModule() override;
};

