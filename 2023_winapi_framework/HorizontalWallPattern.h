#pragma once
#include "BossPattern.h"

class WallAttack;

class HorizontalWallPattern :
    public BossPattern
{
public:
    HorizontalWallPattern(ModuleController* _controller);
    ~HorizontalWallPattern();

public:
    virtual void ExcutePattern() override;

public:
    virtual void SetExcute() override;

private:
    float m_currentTime;
    float m_rotateTimer;
    float m_generateDelay;

    bool m_readyToAttack;

    int m_interval;
    int m_wallCnt;

    int m_dir;

    vector<WallAttack*> m_vecWalls;

};

