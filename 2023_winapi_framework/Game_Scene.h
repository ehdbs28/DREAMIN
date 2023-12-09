#pragma once
#include "Scene.h"

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
    void SetFail();
    void SetClear();

public:
    void Restart();
    void NextStage();

private:
    int m_stageNum;

    float m_executeTimer;
    float m_exexuteDelay;

    bool m_isFailed;
    bool m_isCleared;

};

