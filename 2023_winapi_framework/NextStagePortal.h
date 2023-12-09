#pragma once
#include "Object.h"

class Texture;

class NextStagePortal :
    public Object
{
public:
    NextStagePortal();
    ~NextStagePortal();

public:
    void Update() override;
    void Render(HDC _dc) override;

private:
    Texture* m_pTex;

};

