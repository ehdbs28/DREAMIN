#pragma once
#include "Object.h"

class Texture;

class LoadingScreen :
    public Object
{
public:
    LoadingScreen();
    ~LoadingScreen();

public:
    void Loading(bool _loadOn);
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

public:
    const bool& IsLoadOn() const { return m_loadOn; }
    const bool& IsComplete() const { return m_isComplete; }

private:
    Texture* m_pTex;

    bool m_loadOn;
    bool m_isComplete;

    float m_currentTime;
    float m_loadingDelay;

};

