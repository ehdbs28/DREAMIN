#pragma once
#include "Object.h"

class BackGround :
    public Object
{
public:
    BackGround();
    ~BackGround();

public:
    void Update() override;
    void Render(HDC _dc) override;

private:
    int m_width;
    int m_height;

    float m_parallaxSpeed;

};

