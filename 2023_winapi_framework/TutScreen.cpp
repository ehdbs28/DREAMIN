#include "pch.h"
#include "TutScreen.h"
#include "TextUI.h"
#include "SceneMgr.h"
#include "Game_Scene.h"
#include "Scene.h"

TutScreen::TutScreen()
	: m_dashText(nullptr)
	, m_jumpText(nullptr)
	, m_shotText(nullptr)
	, m_dashClear(false)
	, m_jumpClear(false)
	, m_shotClear(false)
{
}

TutScreen::~TutScreen()
{
	m_dashText = nullptr;
	m_jumpText = nullptr;
	m_shotText = nullptr;
}

void TutScreen::Init()
{
	m_dashText = new TextUI;
	m_dashText->SetText(L"• Z:DASH");
	m_dashText->SetPos(Vec2(50, WINDOW_HEIGHT - 100));
	m_dashText->SetSize(25);
	m_dashText->SetColor(RGB(141, 146, 101));

	m_jumpText = new TextUI;
	m_jumpText->SetText(L"• X:JUMP");
	m_jumpText->SetPos(Vec2(200, WINDOW_HEIGHT - 100));
	m_jumpText->SetSize(25);
	m_jumpText->SetColor(RGB(141, 146, 101));

	m_shotText = new TextUI;
	m_shotText->SetText(L"• C:SHOT");
	m_shotText->SetPos(Vec2(350, WINDOW_HEIGHT - 100));
	m_shotText->SetSize(25);
	m_shotText->SetColor(RGB(141, 146, 101));

	AddObject(m_dashText);
	AddObject(m_jumpText);
	AddObject(m_shotText);
}

void TutScreen::Update()
{
	UIPanel::Update();
	if (m_dashClear && m_jumpClear && m_shotClear) {
		std::static_pointer_cast<Game_Scene>(SceneMgr::GetInst()->GetCurScene())->SetClear();
	}
}

void TutScreen::DashTutClear()
{
	if (m_dashClear) {
		return;
	}
	m_dashClear = true;
	m_dashText->SetColor(RGB(198, 208, 123));
}

void TutScreen::JumpTutClear()
{
	if (m_jumpClear) {
		return;
	}
	m_jumpClear = true;
	m_jumpText->SetColor(RGB(198, 208, 123));
}

void TutScreen::ShotTutClear()
{
	if (m_shotClear) {
		return;
	}
	m_shotClear = true;
	m_shotText->SetColor(RGB(198, 208, 123));
}
