#pragma once
#include "PlayerGroundModule.h"

class PlayerIdleModule :
    public PlayerGroundModule
{
public:
	PlayerIdleModule(ModuleController* _controller);
	virtual ~PlayerIdleModule() override;

public:
	virtual void EnterModule() override;
	virtual void UpdateModule() override;
	virtual void ExitModule() override;
private:
	Vec2 m_inputDir;
};

