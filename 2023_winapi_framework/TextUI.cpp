#include "pch.h"
#include "TextUI.h"

TextUI::TextUI()
	: m_text(L"")
{
}

TextUI::~TextUI()
{
}

void TextUI::Update()
{
}

void TextUI::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	TextOut(_dc, vPos.x, vPos.y, m_text.c_str(), m_text.size());
}
