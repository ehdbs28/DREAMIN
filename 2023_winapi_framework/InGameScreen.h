#pragma once
#include "UIPanel.h"

class SliderUI;
class TextUI;

class InGameScreen :
    public UIPanel
{
public:
    InGameScreen();
    ~InGameScreen();

public:
    virtual void Init() override;

public:
    void SetStatus(bool _dead);
    void SetStage(int _stage);
    void SetBossHpPercent(float _percent);

private:
    SliderUI* m_bossHpSlider;

    TextUI* m_descText;
    int m_stageNum;

};

