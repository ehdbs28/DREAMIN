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
	m_pTex = ResMgr::GetInst()->TexLoad(L"Bullet", L"Texture\\Bullet.bmp");
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
	int Width = m_pTex->GetWidth();
	int Height = m_pTex->GetHeight();

	TransparentBlt(_dc
		, (int)(vPos.x - vScale.x / 2)
		, (int)(vPos.y - vScale.y / 2)
		, Width, Height, m_pTex->GetDC()
		, 0, 0, Width,Height, RGB(255,0,255));
	
	Component_Render(_dc);
}

void Bullet::EnterCollision(Collider* _pOther)
{
}
