#pragma once
#include "UIPanel.h"

class InGameScreen :
    public UIPanel
{
public:
    InGameScreen();
    ~InGameScreen();

public:
    virtual void Init() override;

};

