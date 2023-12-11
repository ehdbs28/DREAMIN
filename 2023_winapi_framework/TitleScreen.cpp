#include "pch.h"
#include "TitleScreen.h"
#include "TextUI.h"
#include "UIObject.h"

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
	titleText->SetSize(250);

	AddObject(titleText);
}
