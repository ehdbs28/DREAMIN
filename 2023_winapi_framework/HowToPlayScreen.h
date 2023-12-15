#pragma once
#include "UIPanel.h"

class HowToPlayScreen :
    public UIPanel
{
public:
    HowToPlayScreen();
    ~HowToPlayScreen();

public:
    virtual void Init() override;
    virtual void Update() override;

private:
    void BackHandle();

};

