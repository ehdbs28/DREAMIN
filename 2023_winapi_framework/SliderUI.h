#pragma once
#include "UIObject.h"

class ImageUI;

class SliderUI :
    public UIObject
{
public:
    SliderUI();
    ~SliderUI();

public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

public:
    virtual void SetPos(Vec2 _vPos) override;
    virtual void SetScale(Vec2 _vScale) override;

public:
    const float& GetPercent() { return m_percent; }

public:
    void SetPercent(float _percent);
    void SetBackImage(wstring _name);
    void SetInnerImage(wstring _name);

private:
    ImageUI* m_backImage;
    ImageUI* m_innerImage;

    float m_percent;

};

