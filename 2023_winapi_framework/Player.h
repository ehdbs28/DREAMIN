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
    const Boss* GetTarget() const { return m_target; }

public:
    void SetTarget(Boss* _target) { m_target = _target; }

private:
    Texture* m_pTex;
    ModuleController* m_pModuleController;

    Boss* m_target;
};

