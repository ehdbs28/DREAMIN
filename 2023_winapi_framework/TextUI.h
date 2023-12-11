#pragma once
#include "UIObject.h"
class TextUI :
    public UIObject
{
public:
    TextUI();
    ~TextUI();

public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

public:
    const std::wstring& GetText() const { return m_text; }

public:
    void SetText(std::wstring _text) { m_text = _text; }

private:
    wstring m_text;

};

