#include "pch.h"
#include "InGameScreen.h"
#include "SliderUI.h"
#include "TextUI.h"

InGameScreen::InGameScreen()
	: m_bossHpSlider(nullptr)
	, m_descText(nullptr)
	, m_stageNum(0)
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

	m_descText = nullptr;

	AddObject(m_bossHpSlider);
}

void InGameScreen::SetStatus(bool _dead)
{
	if (m_descText != nullptr) {
		RemoveObject(m_descText);
	}

	if (_dead) {
		m_descText = new TextUI;
		m_descText->SetText(L"Oops.... You Die.... So Sad....         RESTART: R");
		m_descText->SetPos(Vec2(WINDOW_WIDTH / 2 - 360, WINDOW_HEIGHT - 105));
		m_descText->SetSize(35);
	}
	else {
		m_bossHpSlider->SetPercent(1.f);
		m_descText = new TextUI;
		m_descText->SetPos(Vec2(WINDOW_WIDTH - 125, WINDOW_HEIGHT - 115));
		m_descText->SetSize(50);
		m_descText->SetText(L"#00" + std::to_wstring(m_stageNum));
	}

	if (m_stageNum == 1) {
		m_descText->SetColor(RGB(198, 208, 123));
	}
	else if (m_stageNum == 2) {
		m_descText->SetColor(RGB(91, 110, 225));
	}
	else if (m_stageNum == 3) {
		m_descText->SetColor(RGB(39, 98, 39));
	}

	AddObject(m_descText);
}

void InGameScreen::SetStage(int _stage)
{
	m_stageNum = _stage;
	m_bossHpSlider->SetInnerImage(L"SliderInner" + std::to_wstring(_stage));
	m_descText->SetText(L"#00" + std::to_wstring(m_stageNum));

	if (m_stageNum == 1) {
		m_descText->SetColor(RGB(198, 208, 123));
	}
	else if (m_stageNum == 2) {
		m_descText->SetColor(RGB(91, 110, 225));
	}
	else if (m_stageNum == 3) {
		m_descText->SetColor(RGB(39, 98, 39));
	}
}

void InGameScreen::SetBossHpPercent(float _percent)
{
	m_bossHpSlider->SetPercent(_percent);
}
