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
    void ExitCollision(Collider* _other) override;

public:
    void SetAnimation(wstring _key, bool _repeat, bool _isRight, bool _gravityUnder);
    void SetTarget(Boss* _target) { m_target = _target; }

public:
    const Boss* GetTarget() const { return m_target; }

public:
    void OnDamage(float _damage);
    void DeadHandle() override;

private:
    Texture* m_pTex;
    ModuleController* m_pModuleController;

    Boss* m_target;
};

