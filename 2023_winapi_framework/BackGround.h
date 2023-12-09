#pragma once
#include "Object.h"

class Texture;

class BackGround :
    public Object
{
public:
    BackGround();
    ~BackGround();

public:
    void Setting(int _stage);
    void Update() override;
    void Render(HDC _dc) override;

private:
    Texture* m_pTex;

    int m_width;
    int m_height;

    float m_parallaxSpeed;

};