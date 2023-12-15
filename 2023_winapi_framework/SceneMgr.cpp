#include "pch.h"
#include "SceneMgr.h"
#include "Game_Scene.h"
#include "TitleScene.h"
#include "LoadingScreen.h"

void SceneMgr::Init()
{
	m_pCurScene = nullptr;
	m_pLoadingScreen = new LoadingScreen;
	m_pLoadingScreen->SetPos(Vec2(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f));
	m_pLoadingScreen->SetScale(Vec2(WINDOW_WIDTH, WINDOW_HEIGHT));

	// ¾À µî·Ï
	RegisterScene(L"Title", std::make_shared<TitleScene>());
	RegisterScene(L"Tut", std::make_shared<Game_Scene>(0));
	RegisterScene(L"Stage1", std::make_shared<Game_Scene>(1));
	RegisterScene(L"Stage2", std::make_shared<Game_Scene>(2));
	RegisterScene(L"Stage3", std::make_shared<Game_Scene>(3));

	LoadScene(L"Title");
}

void SceneMgr::Update()
{
	if (m_pLoadingScreen->IsComplete()) {
		if (m_pLoadingScreen->IsLoadOn()) {
			m_pLoadingScreen->Loading(false);
			if (m_pCurScene != nullptr)
			{
				m_pCurScene->Release();
				m_pCurScene = nullptr;
			}

			auto iter = m_mapScenes.find(m_nextSceneName);
			if (iter != m_mapScenes.end())
			{
				m_pCurScene = iter->second;
				m_pCurScene->Init();
			}
		}
		else {
			if (m_pCurScene == nullptr) {
				return;
			}
			m_pCurScene->Update();
			m_pCurScene->FinalUpdate();
		}
	}
	m_pLoadingScreen->Update();
}

void SceneMgr::Render(HDC _dc)
{
	if (m_pCurScene == nullptr) {
		return;
	}
	m_pCurScene->Render(_dc);
}

void SceneMgr::LoadingRender(HDC _dc)
{
	m_pLoadingScreen->Render(_dc);
}

void SceneMgr::LoadScene(const wstring& _scenename)
{
	m_nextSceneName = _scenename;
	m_pLoadingScreen->Loading(true);
}

void SceneMgr::RegisterScene(const wstring& _scenename, std::shared_ptr<Scene> _scene)
{
	m_mapScenes.insert(m_mapScenes.end(), {_scenename, _scene});
}
