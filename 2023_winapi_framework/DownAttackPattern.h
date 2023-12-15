#pragma once
#include "BossPattern.h"

class WallAttack;

class DownAttackPattern :
    public BossPattern
{
public:
    DownAttackPattern(ModuleController* _controller);
    ~DownAttackPattern();

public:
    virtual void ExcutePattern() override;

public:
    virtual void SetExcute() override;

private:
    Vec2 m_originPos;
    Vec2 m_destination;

    float m_currentTime;
    float m_movementTimer;
    float m_downTimer;
    float m_generateDelay;

    bool m_arrived;
    bool m_readyToAttack;
    bool m_isEnd;

    int m_interval;
    int m_wallCnt;

    vector<WallAttack*> m_vecWalls;

};

