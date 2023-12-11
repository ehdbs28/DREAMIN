#pragma once
#include "UIPanel.h"

class CreditsScreen
    : public UIPanel
{
public:
    CreditsScreen();
    ~CreditsScreen();

public:
    virtual void Init() override;
    virtual void Update() override;

private:
    void BackHandle();

};

