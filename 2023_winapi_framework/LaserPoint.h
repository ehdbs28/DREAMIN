#pragma once
#include "Object.h"

class Texture;

class LaserPoint :
    public Object
{
public:
    LaserPoint();
    ~LaserPoint();

public:
    void Update() override;
    void Render(HDC _dc) override;

private:
    Texture* m_pTex;

};

