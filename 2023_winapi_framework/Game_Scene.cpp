#include "pch.h"
#include "Game_Scene.h"
#include "Platform.h"


void Game_Scene::Init()
{
	float platformHeight = (float)WINDOW_HEIGHT / 5.f;
	float platformPoint = platformHeight / 2.f;

	Platform* upperPlatform = new Platform;
	upperPlatform->SetPos(Vec2((float)WINDOW_WIDTH / 2.f, platformPoint));
	upperPlatform->SetScale(Vec2((float)WINDOW_WIDTH, platformHeight));

	Platform* underPlatform = new Platform;
	underPlatform->SetPos(Vec2((float)WINDOW_WIDTH / 2.f, (float)WINDOW_HEIGHT - platformPoint));
	underPlatform->SetScale(Vec2((float)WINDOW_WIDTH, platformHeight));

	AddObject(upperPlatform, OBJECT_GROUP::MAP);
	AddObject(underPlatform, OBJECT_GROUP::MAP);
}

void Game_Scene::Update()
{
	Scene::Update();
}

void Game_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
}

void Game_Scene::Release()
{
	Scene::Release();
}
