#pragma once
#include "Object.h"

class Texture;
class LaserPoint;

class Laser :
    public Object
{
public:
    Laser(float _shotDelay = 1.5f, float _shotTimer = 0.5f, float _destroyTimer = 0.25f);
    ~Laser();

public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    void EnterCollision(Collider* _pOther) override;

public:
    void SetPos(Vec2 _pos) override;

private:
    Texture* m_pLaserTex;

    LaserPoint* m_pPoint;

    float m_curTime;
    float m_shotDelay;
    float m_shotTimer;
    float m_destroyTimer;

    bool m_isShot;
    bool m_isDestroy;
};

