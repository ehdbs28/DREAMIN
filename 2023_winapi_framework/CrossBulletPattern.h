#pragma once
#include "BossPattern.h"

class BossBullet;

class CrossBulletPattern :
    public BossPattern
{
public:
    CrossBulletPattern(ModuleController* _controller);
    ~CrossBulletPattern();

public:
    virtual void ExcutePattern() override;

public:
    virtual void SetExcute() override;

private:
    Vec2 m_originPos;
    Vec2 m_movementPos;

    vector<Vec2> m_dirs;

    int m_bulletCnt;

    float m_currentTime;
    float m_movementTimer;
    float m_generateDelay;

    bool m_isReadyAttack;

    vector<BossBullet*> m_vecBullet;

};

