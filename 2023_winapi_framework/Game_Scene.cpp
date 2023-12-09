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

	m_pPlayer = new Player;
	m_pPlayer->SetName(L"Player");
	m_pPlayer->SetPos(Vec2(100.f, (float)WINDOW_HEIGHT / 2.f));
	m_pPlayer->SetScale(Vec2(80, 80));

	AddObject(backGround, OBJECT_GROUP::BACKGROUND);
	AddObject(upperPlatform, OBJECT_GROUP::MAP);
	AddObject(underPlatform, OBJECT_GROUP::MAP);
	AddObject(m_pPlayer , OBJECT_GROUP::PLAYER);

	if (m_stageNum == 1) {
		m_pBoss = new FirstBoss;
	}
	else if (m_stageNum == 2) {
		m_pBoss = new SecondBoss;
	}
	m_pBoss->SetName(L"Boss" + std::to_wstring(m_stageNum));
	m_pBoss->SetPos(Vec2((float)WINDOW_WIDTH / 2.f, (float)WINDOW_HEIGHT / 3.f));
	m_pBoss->SetScale(Vec2(120, 120));
	AddObject(m_pBoss, OBJECT_GROUP::MONSTER);

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
}
