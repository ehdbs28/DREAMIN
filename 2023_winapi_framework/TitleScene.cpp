#include "pch.h"
#include "TitleScene.h"
#include "BackGround.h"
#include "ResMgr.h"

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
	backGround->Setting(L"StageBackGround0");
	backGround->SetParallaxSpeed(30.f);
	ResMgr::GetInst()->LoadSound(L"LobbyBGM", L"Sound\\LobbyBGM.mp3", true);
	ResMgr::GetInst()->LoadSound(L"UISound", L"Sound\\UISound.wav", false);

	ResMgr::GetInst()->Play(L"LobbyBGM");

	AddObject(backGround, OBJECT_GROUP::BACKGROUND);
}
