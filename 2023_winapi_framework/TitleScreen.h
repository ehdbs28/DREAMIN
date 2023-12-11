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
    virtual void Update() override;

private:
    void StartHandle();
    void HowToPlayHandle();
    void CreditsHandle();
    void QuitHandle();

};

