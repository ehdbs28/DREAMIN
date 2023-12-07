#pragma once
#include "PlayerAirModule.h"

class Rigidbody;

class PlayerJumpModule :
    public PlayerAirModule
{
public:
    PlayerJumpModule(ModuleController* _controller);
    virtual ~PlayerJumpModule();

public:
    virtual void EnterModule() override;
    virtual void UpdateModule() override;
    virtual void ExitModule() override;

private:
    float m_fJumpPower;

    Vec2 m_inputDir;

};

