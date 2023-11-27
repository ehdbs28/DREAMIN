#include "pch.h"
#include "Game_Scene.h"
#include "Platform.h"
#include "Player.h"
#include "CollisionMgr.h"

void Game_Scene::Init()
{
	float platformHeight = (float)WINDOW_HEIGHT / 5.f;
	float platformPoint = platformHeight / 2.f;

	Platform* upperPlatform = new Platform;
	upperPlatform->SetName(L"UPPER_GROUND");
	upperPlatform->SetPos(Vec2((float)WINDOW_WIDTH / 2.f, platformPoint));
	upperPlatform->SetScale(Vec2((float)WINDOW_WIDTH, platformHeight));

	Platform* underPlatform = new Platform;
	underPlatform->SetName(L"UNDER_GROUND");
	underPlatform->SetPos(Vec2((float)WINDOW_WIDTH / 2.f, (float)WINDOW_HEIGHT - platformPoint));
	underPlatform->SetScale(Vec2((float)WINDOW_WIDTH, platformHeight));

	Player* player = new Player;
	player->SetName(L"PLAYER");
	player->SetPos(Vec2((float)WINDOW_WIDTH / 2.f, (float)WINDOW_HEIGHT / 2.f));
	player->SetScale(Vec2(50, 50));

	AddObject(upperPlatform, OBJECT_GROUP::MAP);
	AddObject(underPlatform, OBJECT_GROUP::MAP);
	AddObject(player, OBJECT_GROUP::PLAYER);

	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::MAP, OBJECT_GROUP::PLAYER);
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
