#pragma once
#include "PlayerAirModule.h"
class PlayerFallModule :
    public PlayerAirModule
{
public:
    PlayerFallModule(ModuleController* _controller);
    virtual ~PlayerFallModule();

public:
    virtual void EnterModule() override;
    virtual void UpdateModule() override;
    virtual void ExitModule() override;
};

