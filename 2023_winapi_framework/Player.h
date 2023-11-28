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

private:
    Texture* m_pTex;
    ModuleController* m_pModuleController;

};

