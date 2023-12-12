#pragma once
#include "UIPanel.h"

class SliderUI;

class InGameScreen :
    public UIPanel
{
public:
    InGameScreen();
    ~InGameScreen();

public:
    virtual void Init() override;

public:
    void SetBossHpPercent(float _percent);

private:
    SliderUI* m_bossHpSlider;

};

