#pragma once
#include "BaseModule.h"
#include <random>

class BossIdleModule :
    public BaseModule
{
public:
    BossIdleModule(ModuleController* _controller);
    ~BossIdleModule();

public:
    virtual void EnterModule() override;
    virtual void UpdateModule() override;
    virtual void ExitModule() override;

private:
    float m_cooldownTimer;
    float m_cooldown;

    int m_minCooldown;
    int m_maxCooldown;

};


