#pragma once
#include "UIPanel.h"

class TextUI;

class TutScreen :
    public UIPanel
{
public:
    TutScreen();
    ~TutScreen();

public:
    virtual void Init() override;
    virtual void Update() override;

public:
    void DashTutClear();
    void JumpTutClear();
    void ShotTutClear();

private:
    TextUI* m_dashText;
    TextUI* m_jumpText;
    TextUI* m_shotText;

    bool m_dashClear;
    bool m_jumpClear;
    bool m_shotClear;
};

