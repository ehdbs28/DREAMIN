#pragma once
#include "BossPattern.h"

class MovementPattern :
    public BossPattern
{
public:
    MovementPattern(ModuleController* _controlle);
    ~MovementPattern();

public:
    virtual void ExcutePattern() override;

public:
    virtual void SetExcute() override;

private:
    float EaseInOutCubic(float _x);

private:
    Vec2 m_destinations[4];

    Vec2 m_origin;
    Vec2 m_destination;

    float m_currentTime;
    float m_movementTimer;
    float m_percent;

};

