#pragma once
#include "Scene.h"

class Player;
class Boss;

class Game_Scene :
    public Scene
{
public:
    Game_Scene(int _stageNum);
    ~Game_Scene();

public:
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void Release() override;

public:
    void Restart();
    void Clear();

private:
    int m_stageNum;

};

