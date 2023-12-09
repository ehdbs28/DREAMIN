#include "pch.h"
#include "BackGround.h"
#include "ResMgr.h"
#include "Texture.h"
#include "TimeMgr.h"

BackGround::BackGround()
	: m_width(WINDOW_WIDTH)
	, m_height(WINDOW_HEIGHT)
	, m_parallaxSpeed(100.f)
	, m_pTex(nullptr)
{
}

BackGround::~BackGround()
{
}

void BackGround::Setting(int _stage)
{
	wstring key = L"BackGroundTex" + std::to_wstring(_stage) + L".bmp";
	wstring path = L"Texture\\StageBackGround" + std::to_wstring(_stage) + L".bmp";
	m_pTex = ResMgr::GetInst()->TexLoad(key, path);
}

void BackGround::Update()
{
	Vec2 vPos = GetPos();
	vPos.y += m_parallaxSpeed * fDT;

	if (vPos.y >= 0) {
		vPos.y = -m_height;
	}

	SetPos(vPos);
}

void BackGround::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	long width = m_pTex->GetWidth();
	long height = m_pTex->GetHeight();
	StretchBlt(_dc,
		0, vPos.y,
		m_width, m_height * 2,
		m_pTex->GetDC(),
		0, 0, width, height,
		SRCCOPY
	);
}
