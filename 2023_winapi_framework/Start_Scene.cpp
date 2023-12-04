#include "pch.h"
#include "Start_Scene.h"
#include "Object.h"
#include "Core.h"
#include "Player.h"
#include "KeyMgr.h"
#include "CollisionMgr.h"
#include "ResMgr.h"
void Start_Scene::Init()
{
	Object* pObj = new Player;
	pObj->SetPos((Vec2({Core::GetInst()->GetResolution().x /2, Core::GetInst()->GetResolution().y / 2})));
	pObj->SetScale(Vec2(100.f,100.f));
	AddObject(pObj, OBJECT_GROUP::PLAYER);

	// ���� ���� �������� ��ġ�� �غ��ô�.

	ResMgr::GetInst()->LoadSound(L"BGM", L"Sound\\Retro_bgm.wav", true);
	ResMgr::GetInst()->LoadSound(L"Shoot", L"Sound\\laserShoot.wav", false);
	ResMgr::GetInst()->Play(L"BGM");

	// �浹üũ�ؾߵǴ°͵��� ��������.
	CollisionMgr::GetInst()->CheckGroup(OBJECT_GROUP::BULLET, OBJECT_GROUP::MONSTER);
}

void Start_Scene::Update()
{
	Scene::Update();
	//if(KEY_DOWN(KEY_TYPE::ENTER))
	//	// �� ����
}

void Start_Scene::Render(HDC _dc)
{
	Scene::Render(_dc);
}

void Start_Scene::Release()
{
	Scene::Release();
	CollisionMgr::GetInst()->CheckReset();
}
