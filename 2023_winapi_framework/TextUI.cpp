#include "pch.h"
#include "TextUI.h"
#include "SelectGDI.h"
#include "ResMgr.h"

TextUI::TextUI()
	: m_text(L"")
	, m_font(L"NeoµÕ±Ù¸ð Pro")
	, m_size(50)
	, m_textColor(RGB(255, 255, 255))
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
	HFONT hFont = ResMgr::GetInst()->LoadFont(m_font, m_size);
	SelectGDI gdi(_dc, hFont);
	SetTextColor(_dc, m_textColor);
	TextOut(_dc, vPos.x, vPos.y, m_text.c_str(), m_text.size());
	DeleteObject(hFont);
}
