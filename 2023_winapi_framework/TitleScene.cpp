#include "pch.h"
#include "TitleScene.h"
#include "BackGround.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	BackGround* backGround = new BackGround;
	backGround->SetName(L"BackGruond");
	backGround->SetPos(Vec2(0, -WINDOW_HEIGHT));
	backGround->Setting(L"TitleBackGround");
	backGround->SetParallaxSpeed(30.f);

	AddObject(backGround, OBJECT_GROUP::BACKGROUND);
}
