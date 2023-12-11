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
    void Setting(wstring _name);
    void Update() override;
    void Render(HDC _dc) override;

public:
    void SetParallaxSpeed(float _speed) { m_parallaxSpeed = _speed; }

private:
    Texture* m_pTex;

    int m_width;
    int m_height;

    float m_parallaxSpeed;

};