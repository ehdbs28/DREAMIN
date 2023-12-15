#pragma once
#include "BossPattern.h"

class Laser;

class BossLaserAroundPattern :
    public BossPattern
{
public:
    BossLaserAroundPattern(ModuleController* _controller);
    ~BossLaserAroundPattern();

public:
    virtual void ExcutePattern() override;

public:
    virtual void SetExcute() override;

private:
    int m_bulletCnt;
    int m_angle;
    int m_interval;

    float m_currentTime;
    float m_generateDelay;

    vector<Laser*> m_vecLaser;

};

