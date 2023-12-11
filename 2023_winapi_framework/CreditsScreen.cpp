#include "pch.h"
#include "CreditsScreen.h"
#include "UIManager.h"
#include "KeyMgr.h"
#include "TextUI.h"

CreditsScreen::CreditsScreen()
{
}

CreditsScreen::~CreditsScreen()
{
}

void CreditsScreen::Init()
{
	TextUI* titleText = new TextUI;
	titleText->SetText(L"Credits");
	titleText->SetPos(Vec2(75, 50));
	titleText->SetSize(70);

	TextUI* programmingText = new TextUI;
	programmingText->SetText(L"Programming by:");
	programmingText->SetPos(Vec2(75, 150));
	programmingText->SetSize(30);
	TextUI* ehdns28Text1 = new TextUI;
	ehdns28Text1->SetText(L"ehdbs28");
	ehdns28Text1->SetPos(Vec2(75, 200));
	ehdns28Text1->SetSize(30);
	TextUI* kangjh0214Text1 = new TextUI;
	kangjh0214Text1->SetText(L"kangjh0214");
	kangjh0214Text1->SetPos(Vec2(75, 250));
	kangjh0214Text1->SetSize(30);

	TextUI* artText = new TextUI;
	artText->SetText(L"Art by:");
	artText->SetPos(Vec2(75, 300));
	artText->SetSize(30);
	TextUI* ehdns28Text2 = new TextUI;
	ehdns28Text2->SetText(L"ehdbs28");
	ehdns28Text2->SetPos(Vec2(75, 350));
	ehdns28Text2->SetSize(30);
	TextUI* kangjh0214Text2 = new TextUI;
	kangjh0214Text2->SetText(L"kangjh0214");
	kangjh0214Text2->SetPos(Vec2(75, 400));
	kangjh0214Text2->SetSize(30);

	TextUI* infoText = new TextUI;
	infoText->SetText(L"ESC to go back");
	infoText->SetPos(Vec2(75, 480));
	infoText->SetSize(30);
	infoText->SetColor(RGB(150, 150, 150));

	AddObject(titleText);
	AddObject(programmingText);
	AddObject(ehdns28Text1);
	AddObject(kangjh0214Text1);
	AddObject(artText);
	AddObject(ehdns28Text2);
	AddObject(kangjh0214Text2);
	AddObject(infoText);
}

void CreditsScreen::Update()
{
	UIPanel::Update();
	if (KEY_DOWN(KEY_TYPE::ESC)) {
		BackHandle();
	}
}

void CreditsScreen::BackHandle()
{
	UIManager::GetInst()->ReturnUI();
}
