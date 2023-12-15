#pragma once
#include "Object.h"

class Texture;

class Bullet :
    public Object
{
public:
    Bullet(OBJECT_GROUP _ownerObjectGroup);
    virtual ~Bullet();

public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    void EnterCollision(Collider* _pOther) override;

public:
    void SetDir(Vec2 _dir) {
        m_dir = _dir.Normalize();
        SetAngle(atan2f(m_dir.y, m_dir.x) * (180.f / M_PI));
    }
    void SetDamage(int _damage) { m_damage = _damage; }
    void SetSpeed(int _speed) { m_fSpeed = _speed; }

public:
    void Destroy();

protected:
    virtual void GenerateDestroyParticle();

protected:
    Texture* m_pTex;

    OBJECT_GROUP m_ownerObjectGroup;

    Vec2 m_dir;

    float m_fSpeed;
    int m_damage;

};

