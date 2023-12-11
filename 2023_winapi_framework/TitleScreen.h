#pragma once
#include "UIPanel.h"
class TitleScreen :
    public UIPanel
{
public:
    TitleScreen();
    ~TitleScreen();

public:
    virtual void Init() override;

};

