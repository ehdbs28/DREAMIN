#include "pch.h"
#include "Game_Scene.h"
#include "Platform.h"
#include "Player.h"
#include "CollisionMgr.h"
#include "FirstBoss.h"
#include "SecondBoss.h"
#include "BackGround.h"
#include "Player.h"
#include "Boss.h"
#include "SceneMgr.h"

Game_Scene::Game_Scene(int _stageNum)
	: m_stageNum(_stageNum)
{
}

Game_Scene::~Game_Scene()
{
}

void Game_Scene::Init()
{
	float platformHeight = (float)WINDOW_HEIGHT / 5.f;
	float platformPoint = platformHeight / 2.f;

	Platform* upperPlatform = new Platform;
	upperPlatform->SetName(L"UpperGround");
	upperPlatform->SetPos(Vec2((float)WINDOW_WIDTH / 2.f, platformPoint));
	upperPlatform->SetScale(Vec2((float)WINDOW_WIDTH, platformHeight));

	Platform* underPlatform = new Platform;
	underPlatform->SetName(L"UnderGround");
	underPlatform->SetPos(Vec2((float)WINDOW_WIDTH / 2.f, (float)WINDOW_HEIGHT - platformPoint));
	underPlatform->SetScale(Vec2((float)WINDOW_WIDTH, platformHeight));

	BackGround* backGround = new BackGround;
	backGround->SetName(L"BackGround");
	backGround->SetPos(Vec2(0, -WINDOW_HEIGHT));
	backGround->Setting(m_stageNum);

	Player* player = new Player;
	player->SetName(L"Player");
	player->SetPos(Vec2(100.f, (float)WINDOW_HEIGHT / 2.f));
	player->SetScale(Vec2(80, 80));

	AddObject(backGround, OBJECT_GROUP::BACKGROUND);
	AddObject(player, OBJECT_GROUP::PLAYER);
	AddObject(upperPlatform, OBJECT_GROUP::MAP);
	AddObject(underPlatform, OBJECT_GROUP::MAP);

	Boss* boss = nullptr;
	if (m_stageNum == 1) {
		boss = new FirstBoss;
	}
	else if (m_stageNum == 2) {
		boss = new SecondBoss;
	}
	boss->SetName(L"Boss" + std::to_wstring(m_stageNum));
	boss->SetPos(Vec2((float)WINDOW_WIDTH / 2.f, (float)WINDOW_HEIGHT / 3.f));
	boss->SetScale(Vec2(120, 120));
	AddObject(boss, OBJECT_GROUP::MONSTER);

	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::PLAYER, OBJECT_GROUP::MAP);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::BULLET, OBJECT_GROUP::MAP);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::BULLET, OBJECT_GROUP::PLAYER);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::BULLET, OBJECT_GROUP::MONSTER);
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

void Game_Scene::Restart()
{
}

void Game_Scene::Clear()
{
	SceneMgr::GetInst()->LoadScene(L"Stage2");
}
