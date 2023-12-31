#pragma once
#include "PlayerGroundModule.h"

class PlayerMovementModule : public PlayerGroundModule
{
public:
	PlayerMovementModule(ModuleController* _controller);
	virtual ~PlayerMovementModule() override;

public:
	virtual void EnterModule() override;
	virtual void UpdateModule() override;
	virtual void ExitModule() override;

private:
	float m_fMovementSpeed;

};

