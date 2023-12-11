#include "pch.h"
#include "TitleScreen.h"
#include "TextUI.h"
#include "UIObject.h"
#include "KeyMgr.h"
#include "UIManager.h"
#include "UIMenuSystem.h"
#include "UIMenu.h"
#include "ImageUI.h"
#include "Core.h"

TitleScreen::TitleScreen()
{
}

TitleScreen::~TitleScreen()
{
}

void TitleScreen::Init()
{
	ImageUI* titleBox = new ImageUI;
	titleBox->SetScale(Vec2(400, 125));
	titleBox->SetPos(Vec2(WINDOW_WIDTH / 2 - 205, 50));
	titleBox->SetTexture(L"UnSelectedBox");

	TextUI* titleText = new TextUI;
	titleText->SetText(L"TITLE");
	titleText->SetPos(Vec2(WINDOW_WIDTH / 2 - 130, 70));
	titleText->SetSize(100);

	UIMenuSystem* menuSystem = new UIMenuSystem;
	menuSystem->SetPos(Vec2(100, 250));
	menuSystem->AddMenu(new UIMenu, L"Start", std::bind(&TitleScreen::StartHandle, this));
	menuSystem->AddMenu(new UIMenu, L"How to play", std::bind(&TitleScreen::HowToPlayHandle, this));
	menuSystem->AddMenu(new UIMenu, L"Credits", std::bind(&TitleScreen::CreditsHandle, this));
	menuSystem->AddMenu(new UIMenu, L"Quit", std::bind(&TitleScreen::QuitHandle, this));

	AddObject(titleBox);
	AddObject(titleText);
	AddObject(menuSystem);
}

void TitleScreen::StartHandle()
{
}

void TitleScreen::HowToPlayHandle()
{
	UIManager::GetInst()->LoadPanel(L"HowToPlay");
}

void TitleScreen::CreditsHandle()
{
	UIManager::GetInst()->LoadPanel(L"Credits");
}

void TitleScreen::QuitHandle()
{
	HWND hWnd = Core::GetInst()->GetHwnd();
	SendMessage(hWnd, WM_CLOSE, 0, 0);
}
