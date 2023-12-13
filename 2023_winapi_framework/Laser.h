#pragma once
#include "Object.h"

class Texture;
class LaserPoint;

class Laser :
    public Object
{
public:
    Laser(float _shotDelay = 1.5f, float _shotTimer = 0.5f);
    ~Laser();

public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    void EnterCollision(Collider* _pOther) override;

public:
    void SetDir(Vec2 _dir) { m_laserDir = _dir; }
    void SetPos(Vec2 _pos) override;

private:
    Vec2 m_laserDir;
    Texture* m_pLaserTex;

    LaserPoint* m_pPoint;

    float m_curTime;
    float m_shotDelay;
    float m_shotTimer;

    bool m_isShot;
};

