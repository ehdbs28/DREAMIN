#pragma once
#include "Object.h"

class Texture;
class ModuleController;

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
    const int& GetGravityDir() const { return m_gravityDir; }
    const bool& IsGround() const { return m_isGround; }

public:
    void ChangeGravity();

private:
    Texture* m_pTex;
    ModuleController* m_pModuleController;

    int m_gravityDir;
    bool m_isGround;

};

