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

private:
    SliderUI* m_bossHpSlider;

};

