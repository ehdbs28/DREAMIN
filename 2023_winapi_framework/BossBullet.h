#pragma once
#include "Bullet.h"

class Texture;
class Player;

class BossBullet :
    public Bullet
{
public:
    BossBullet(OBJECT_GROUP _ownerObjectGroup, bool _following = false, const Player* _pTarget = nullptr, float _lifeTime = 4.f);
    virtual ~BossBullet();

public:
    void Update() override;

protected:
    virtual void GenerateDestroyParticle() override;

private:
    bool m_following;
    const Player* m_pTarget;

    float m_currentTime;
    float m_lifeTime;

};

