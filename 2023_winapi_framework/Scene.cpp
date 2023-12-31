#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "EventMgr.h"
#include "CollisionMgr.h"

Scene::Scene()
{
}

Scene::~Scene()
{
	Release();
}

void Scene::Update()
{
	for (UINT i = 0; i < (UINT)OBJECT_GROUP::END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size();)
		{
			if(!m_vecObj[i][j]->GetIsDead())
				m_vecObj[i][j++]->Update();
			else
				m_vecObj[i].erase(m_vecObj[i].begin() + j);
		}
	}
}

void Scene::FinalUpdate()
{
	for (UINT i = 0; i < (UINT)OBJECT_GROUP::END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); ++j)
		{
			m_vecObj[i][j]->FinalUpdate();
		}
	}
}

void Scene::Render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)OBJECT_GROUP::END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); ++j)
		{
			if (!m_vecObj[i][j]->GetIsDead())
				m_vecObj[i][j]->Render(_dc);
		}
	}
}

void Scene::Release()
{
	CollisionMgr::GetInst()->CheckReset();
	for (UINT i = 0; i < (UINT)OBJECT_GROUP::END; ++i)
	{
		for (size_t j = 0; j < m_vecObj[i].size(); ++j)
		{
			//delete m_vecObj[i][j];
			EventMgr::GetInst()->DeleteObject(m_vecObj[i][j]);
		}
		m_vecObj[i].clear();
	}
}
