#include "pch.h"
#include "Core.h"
#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
#include "ResMgr.h"
#include "CollisionMgr.h"
#include "EventMgr.h"
#include <ctime>
#include "UIManager.h"
#include "CameraManager.h"

bool Core::Init(HWND _hWnd, POINT _ptResolution)
{
	// === 변수 초기화 === 
	m_hWnd = _hWnd;
	m_ptResolution = _ptResolution;
	m_hbackDC = 0;
	m_hbackbit = 0;


	// 더블버퍼링
	m_hDC = GetDC(m_hWnd);	
	// 1. 생성
	m_hbackbit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_hbackDC = CreateCompatibleDC(m_hDC);

	// 2. 연결
	SelectObject(m_hbackDC, m_hbackbit);

//	m_obj.SetPos(Vec2({ m_ptResolution.x / 2, m_ptResolution.y / 2 }));
////	m_obj.m_ptPos = ;
//	m_obj.SetScale(Vec2(150, 150));

	CreateGDI();

	srand((UINT)time(nullptr));

	// ==== Manager Init ====
	PathMgr::GetInst()->Init();
	TimeMgr::GetInst()->Init();
	CameraManager::GetInst()->Init(Vec2(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f));
	KeyMgr::GetInst()->Init();
	ResMgr::GetInst()->Init();
	UIManager::GetInst()->Init();
	SceneMgr::GetInst()->Init();

	return true;
}

void Core::GameLoop()
{
	/*static int count = 0;
	++count;
	static int prev = GetTickCount64();
	int cur = GetTickCount64();
	if (cur - prev > 1000)
	{
		prev = cur;
		count = 0;
	}*/
	Update();
	Render();
	EventMgr::GetInst()->Update();
}


void Core::Update()
{
	// === Manager Update === 
	TimeMgr::GetInst()->Update();
	CameraManager::GetInst()->Update();
	KeyMgr::GetInst()->Update();
	UIManager::GetInst()->Update();
	CollisionMgr::GetInst()->Update();
	SceneMgr::GetInst()->Update();
}

void Core::Render()
{
	PatBlt(m_hbackDC, 0, 0, m_ptResolution.x, m_ptResolution.y, BLACKNESS);

	SceneMgr::GetInst()->Render(m_hbackDC);
	UIManager::GetInst()->Render(m_hbackDC);
	SceneMgr::GetInst()->LoadingRender(m_hbackDC);

	Vec2 vCenter = CameraManager::GetInst()->GetShakingPos();

	BitBlt(m_hDC,
		vCenter.x - m_ptResolution.x / 2.f, vCenter.y - m_ptResolution.y / 2.f,
		m_ptResolution.x, m_ptResolution.y,
		m_hbackDC, 0,0, SRCCOPY);
}

void Core::CreateGDI()
{
	// HOLLOW
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::RED] = (HBRUSH)CreateSolidBrush(RGB(255, 167, 167));
	m_arrBrush[(UINT)BRUSH_TYPE::GREEN] = (HBRUSH)CreateSolidBrush(RGB(134, 229, 134));
	m_arrBrush[(UINT)BRUSH_TYPE::BLUE] = (HBRUSH)CreateSolidBrush(RGB(103, 153, 255));
	m_arrBrush[(UINT)BRUSH_TYPE::YELLOW] = (HBRUSH)CreateSolidBrush(RGB(255, 187, 0));

	//RED GREEN BLUE PEN
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::YELLOW] = CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::HOLLOW] = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
}

void Core::Release()
{
	ReleaseDC(m_hWnd, m_hDC);
	DeleteDC(m_hbackDC); // createdc 한거 지우는거
	DeleteObject(m_hbackbit); // createbit 한거 지우는거
	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
	for (int i = 1; i < (UINT)BRUSH_TYPE::END; ++i)
	{
		DeleteObject(m_arrBrush[i]);
	}

	ResMgr::GetInst()->Release();
}