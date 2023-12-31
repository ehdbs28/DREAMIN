#pragma once
#include "Object.h"

class Texture;
class ModuleController;
class Boss;

class Player :
    public Object
{
public:
    Player();
    ~Player();

public:
    void Update() override;
    void Render(HDC _dc) override;

public:
    void EnterCollision(Collider* _other) override;
    void StayCollision(Collider* _other) override;
    void ExitCollision(Collider* _other) override;

public:
    void SetAnimation(wstring _key, bool _repeat, bool _isRight, bool _gravityUnder);
    void SetTarget(Boss* _target) { m_target = _target; }
    void SetInvincibility(bool _invincibility) { m_isInvincibility = _invincibility; }

public:
    const Boss* GetTarget() const { return m_target; }
    const bool& IsInvincibility() const { return m_isInvincibility; }

public:
    void OnDamage(float _damage);
    void DeadHandle() override;

private:
    Texture* m_pTex;
    ModuleController* m_pModuleController;

    Boss* m_target;

    bool m_isInvincibility;

};

