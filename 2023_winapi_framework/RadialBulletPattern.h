#pragma once
#include "BossPattern.h"

class BossBullet;

class RadialBulletPattern :
    public BossPattern
{
public:
    RadialBulletPattern(ModuleController* _controller);
    ~RadialBulletPattern();

public:
    virtual void ExcutePattern() override;

public:
    virtual void SetExcute() override;

private:
    int m_bulletCnt;
    int m_angle;
    int m_interval;

    float m_currentTime;
    float m_rotateTime;
    float m_rotateTimer;
    float m_generateDelay;

    vector<BossBullet*> m_vecBullet;
};

