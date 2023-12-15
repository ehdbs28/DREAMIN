#pragma once
#include "BossPattern.h"

class BossBullet;

class FollowBulletPattern :
    public BossPattern
{
public:
    FollowBulletPattern(ModuleController* _controller);
    ~FollowBulletPattern();

public:
    virtual void ExcutePattern() override;

public:
    virtual void SetExcute() override;

private:
    int m_bulletCnt;

    float m_currentTime;
    float m_generateDelay;

    vector<BossBullet*> m_vecBullet;

};

