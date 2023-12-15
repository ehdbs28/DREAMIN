#pragma once
#include "Bullet.h"

class Texture;
class Player;

class BossBullet :
    public Bullet
{
public:
    BossBullet(OBJECT_GROUP _ownerObjectGroup, bool _following = false, Player* _pTarget);
    virtual ~BossBullet();

public:
    void Update() override;

protected:
    virtual void GenerateDestroyParticle() override;

private:
    bool m_following;
    Player* m_pTarget;

};

