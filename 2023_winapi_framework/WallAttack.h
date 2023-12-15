#pragma once
#include "Object.h"

class Texture;

class WallAttack :
    public Object
{
public:
    WallAttack(float _enableTimer = 0.3f, float _attackTimer = 1.f);
    ~WallAttack();

public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    void StayCollision(Collider* _pOther) override;

private:
    Texture* m_pTex;

    float m_currentTime;
    float m_enableTimer;
    float m_attackTimer;

    bool m_isAttack;
    bool m_isDestroy;

};

