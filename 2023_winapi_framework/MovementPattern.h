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
    void SelectDestination();
    void ShuffleOrder();

private:
    Vec2 m_destinations[4];
    int m_order[4];
    int m_index;

    Vec2 m_origin;
    Vec2 m_destination;

    float m_currentTime;
    float m_movementTimer;
    float m_percent;

};

