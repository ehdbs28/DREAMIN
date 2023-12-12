#include "pch.h"
#include "InGameScreen.h"
#include "SliderUI.h"
#include "TextUI.h"

InGameScreen::InGameScreen()
	: m_bossHpSlider(nullptr)
{
}

InGameScreen::~InGameScreen()
{
}

void InGameScreen::Init()
{
	m_bossHpSlider = new SliderUI;
	m_bossHpSlider->SetBackImage(L"SliderBack");
	m_bossHpSlider->SetInnerImage(L"SliderInner1");
	m_bossHpSlider->SetScale(Vec2(550, 25));
	m_bossHpSlider->SetPos(Vec2(10, 85));

	TextUI* bossNameText = new TextUI;
	bossNameText->SetPos(Vec2(WINDOW_WIDTH - 125, WINDOW_HEIGHT - 115));
	bossNameText->SetSize(50);
	bossNameText->SetText(L"#001");
	bossNameText->SetColor(RGB(230, 230, 230));

	AddObject(m_bossHpSlider);
	AddObject(bossNameText);
}
