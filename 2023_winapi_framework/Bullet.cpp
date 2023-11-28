#include "pch.h"
#include "Bullet.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "Texture.h"
Bullet::Bullet(OBJECT_GROUP _ownerObjectGroup)
	: m_ownerObjectGroup(_ownerObjectGroup)
	, m_dir(Vec2(0.f, 0.f))
	, m_fSpeed(1000.f)
	, m_pTex(nullptr)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Bullet", L"Texture\\plane.bmp");
	CreateCollider();
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	Vec2 vPos = GetPos();
	vPos.x += m_fSpeed * fDT * m_dir.x;
	vPos.y += m_fSpeed * fDT * m_dir.y;
	SetPos(vPos);
}

void Bullet::Render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	float angle = GetAngle();
	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();

	POINT tPoint[3] = { 0, };
	float fx, fy, fxDest, fyDest;
	float fRadian = angle * (M_PI / 180.f);
	float cosTheta = cosf(fRadian);
	float sinTheta = sinf(fRadian);

	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			fx = -vScale.x / 2.f;
			fy = -vScale.y / 2.f;
		}
		else if (i == 1) {
			fx = vScale.x / 2.f;
			fy = -vScale.y / 2.f;
		}
		else {
			fx = -vScale.x / 2.f;
			fy = vScale.y / 2.f;
		}

		fxDest = fx * cosTheta - fy * sinTheta;
		fyDest = fy * sinTheta + fy * cosTheta;
		tPoint[i].x = fxDest + vPos.x;
		tPoint[i].y = fyDest + vPos.y;
	}

	HDC tempDC = CreateCompatibleDC(_dc);
	HBITMAP tempBitmap = CreateCompatibleBitmap(_dc, Width, Height);
	SelectObject(tempDC, tempBitmap);
	PatBlt(tempDC, 0, 0, Width, Height, TRANSPARENT);

	TransparentBlt(
		tempDC,
		0, 0, Width, Height,
		m_pTex->GetDC(),
		0, 0, Width,Height,
		RGB(255,0,255)
	);

	PlgBlt(_dc,
		tPoint,
		tempDC,
		0, 0, Width, Height,
		nullptr, 0, 0
	);
	
	Component_Render(_dc);

	DeleteDC(tempDC);
	DeleteObject(tempBitmap);
}

void Bullet::EnterCollision(Collider* _pOther)
{
}
