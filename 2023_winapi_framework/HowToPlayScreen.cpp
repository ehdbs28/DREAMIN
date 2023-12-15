#include "pch.h"
#include "HowToPlayScreen.h"
#include "UIManager.h"
#include "KeyMgr.h"
#include "TextUI.h"

HowToPlayScreen::HowToPlayScreen()
{
}

HowToPlayScreen::~HowToPlayScreen()
{
}

void HowToPlayScreen::Init()
{
	TextUI* titleText = new TextUI;
	titleText->SetText(L"How to play");
	titleText->SetPos(Vec2(75, 50));
	titleText->SetSize(70);

	TextUI* moveDescText = new TextUI;
	moveDescText->SetText(L"1: AD to move");
	moveDescText->SetPos(Vec2(75, 200));
	moveDescText->SetSize(30);
	TextUI* dashDescText = new TextUI;
	dashDescText->SetText(L"2: Z to dash from movement direction");
	dashDescText->SetPos(Vec2(75, 250));
	dashDescText->SetSize(30);
	TextUI* jumpDescText = new TextUI;
	jumpDescText->SetText(L"3: X to jump");
	jumpDescText->SetPos(Vec2(75, 300));
	jumpDescText->SetSize(30);
	TextUI* attackDescText = new TextUI;
	attackDescText->SetText(L"4: C to shot bullet");
	attackDescText->SetPos(Vec2(75, 350));
	attackDescText->SetSize(30);

	TextUI* infoText = new TextUI;
	infoText->SetText(L"ESC to go back");
	infoText->SetPos(Vec2(75, 430));
	infoText->SetSize(30);
	infoText->SetColor(RGB(150, 150, 150));

	AddObject(titleText);
	AddObject(moveDescText);
	AddObject(dashDescText);
	AddObject(jumpDescText);
	AddObject(attackDescText);
	AddObject(infoText);
}

void HowToPlayScreen::Update()
{
	UIPanel::Update();
	if (KEY_DOWN(KEY_TYPE::ESC)) {
		BackHandle();
	}
}

void HowToPlayScreen::BackHandle()
{
	UIManager::GetInst()->ReturnUI();
}
