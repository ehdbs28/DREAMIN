#pragma once
#include "Object.h"

class Texture;

class Particle :
    public Object
{
public:
    Particle(PARTICLE_TYPE _type, float _duration, bool _repeat);
    ~Particle();

public:
    void Update() override;
    void Render(HDC _dc) override;

private:
    PARTICLE_TYPE m_type;
    Texture* m_pTex;

    float m_duration;
    float m_durationTimer;

    bool m_repeat;

};

