#pragma once
#include "BaseModule.h"
class PlayerAirModule :
    public BaseModule
{
public:
    PlayerAirModule(ModuleController* _controller);
    ~PlayerAirModule();

public:
    void UpdateModule() override;

private:
    float m_fMovementSpeed;
    Vec2 m_inputDir;

};

