#pragma once
#include "BossPattern.h"

class Laser;

class LaserPattern :
    public BossPattern
{
public:
    LaserPattern(ModuleController* _controller);
    ~LaserPattern();

public:
    virtual void ExcutePattern() override;

private:
    float m_rotateSpeed;
    Laser* m_pLaser;

};

