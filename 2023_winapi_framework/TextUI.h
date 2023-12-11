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
    const std::wstring& GetFont() const { return m_font; }
    const int& GetSize() const { return m_size; }

public:
    void SetText(std::wstring _text) { m_text = _text; }
    void SetFont(std::wstring _font) { m_font = _font; }
    void SetSize(int _size) { m_size = _size; }

private:
    wstring m_text;
    wstring m_font;

    int m_size;

};

