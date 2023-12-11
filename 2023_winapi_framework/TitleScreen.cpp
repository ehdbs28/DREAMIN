#include "pch.h"
#include "TitleScreen.h"
#include "TextUI.h"
#include "UIObject.h"
#include "KeyMgr.h"
#include "UIManager.h"
#include "UIMenuSystem.h"
#include "UIMenu.h"

TitleScreen::TitleScreen()
{
}

TitleScreen::~TitleScreen()
{
}

void TitleScreen::Init()
{
	TextUI* titleText = new TextUI;
	titleText->SetText(L"TITLE");
	titleText->SetSize(100);

	UIMenuSystem* menuSystem = new UIMenuSystem;
	menuSystem->SetPos(Vec2(100, 300));
	menuSystem->AddMenu(new UIMenu, L"Start", nullptr);
	menuSystem->AddMenu(new UIMenu, L"How To Play", nullptr);
	menuSystem->AddMenu(new UIMenu, L"Credits", nullptr);
	menuSystem->AddMenu(new UIMenu, L"Quit", nullptr);

	AddObject(titleText);
	AddObject(menuSystem);
}

void TitleScreen::Update()
{
	UIPanel::Update();
}
