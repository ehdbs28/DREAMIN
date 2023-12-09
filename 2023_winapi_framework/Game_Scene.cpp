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
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "NextStagePortal.h"

Game_Scene::Game_Scene(int _stageNum)
	: m_stageNum(_stageNum)
	, m_executeTimer(0.f)
	, m_exexuteDelay(0.5f)
	, m_isCleared(false)
	, m_isFailed(false)
{
}

Game_Scene::~Game_Scene()
{
}

void Game_Scene::Init()
{
	m_isCleared = false;
	m_isFailed = false;
	m_executeTimer = 0.f;

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
	player->SetPos(Vec2(100.f, (float)WINDOW_HEIGHT - platformPoint));
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

	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::MAP, OBJECT_GROUP::PLAYER);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::MAP, OBJECT_GROUP::BULLET);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::BULLET, OBJECT_GROUP::PLAYER);
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::BULLET, OBJECT_GROUP::MONSTER);
}

void Game_Scene::Update()
{
	Scene::Update();

	if (m_isFailed) {
		if (m_executeTimer < m_exexuteDelay) {
			m_executeTimer += fDT;
		}
		else {
			m_executeTimer = m_exexuteDelay;
		}

		if (KEY_PRESS(KEY_TYPE::R)) {
			Restart();
		}
	}
}

void Game_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);

	if (!m_isFailed) {
		return;
	}

	HDC tempDC = CreateCompatibleDC(_dc);
	HBITMAP tempBitmap = CreateCompatibleBitmap(_dc, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(tempDC, tempBitmap);
	PatBlt(tempDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, BLACKNESS);

	float percent = m_executeTimer / m_exexuteDelay;

	BLENDFUNCTION bf;
	bf.BlendOp = 0;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = 200 * percent;
	bf.AlphaFormat = AC_SRC_OVER;

	GdiAlphaBlend(
		_dc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		tempDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		bf
	);

	DeleteObject(tempBitmap);
	DeleteDC(tempDC);
}

void Game_Scene::Release()
{
	Scene::Release();
}

void Game_Scene::SetFail()
{
	m_isFailed = true;
}

void Game_Scene::SetClear()
{
	m_isCleared = true;

	NextStagePortal* portal = new NextStagePortal;
	portal->SetName(L"Portal");
	portal->SetPos(Vec2(WINDOW_WIDTH / 2, WINDOW_HEIGHT - WINDOW_HEIGHT / 5 - 55));
	portal->SetScale(Vec2(110, 110));
	AddObject(portal, OBJECT_GROUP::MAP);
}

void Game_Scene::Restart()
{
	wstring nextStage = L"Stage" + std::to_wstring(m_stageNum);
	SceneMgr::GetInst()->LoadScene(nextStage);
}

void Game_Scene::NextStage()
{
	m_isCleared = true;
	if (m_stageNum > MAX_STAGE) {
		//
		Release();
	}
	else {
		wstring nextStage = L"Stage" + std::to_wstring(m_stageNum + 1);
		SceneMgr::GetInst()->LoadScene(nextStage);
	}
}
