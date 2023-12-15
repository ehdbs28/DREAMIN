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
    const COLORREF& GetColor() const { return m_textColor; }

public:
    void SetText(std::wstring _text) { m_text = _text; }
    void SetFont(std::wstring _font) { m_font = _font; }
    void SetSize(int _size) { m_size = _size; }
    void SetColor(COLORREF _color) { m_textColor = _color; }

private:
    wstring m_text;
    wstring m_font;

    COLORREF m_textColor;

    int m_size;

};

