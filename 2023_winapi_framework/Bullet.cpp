#include "pch.h"
#include "Bullet.h"
#include "TimeMgr.h"
#include "ResMgr.h"
#include "Texture.h"
#include "EventMgr.h"
#include "Collider.h"
#include "Core.h"
#include "Boss.h"
#include "Player.h"
#include "Particle.h"
#include "SceneMgr.h"
#include "Scene.h"

Bullet::Bullet(OBJECT_GROUP _ownerObjectGroup)
	: m_ownerObjectGroup(_ownerObjectGroup)
	, m_dir(Vec2(0.f, 0.f))
	, m_fSpeed(1000.f)
	, m_pTex(nullptr)
	, m_damage(0)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Bullet", L"Texture\\Bullet.bmp");
	CreateCollider();
	GetCollider()->SetScale(Vec2(20.f, 50.f));
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	Vec2 vPos = GetPos();

	if (vPos.x < 0 || vPos.x > WINDOW_WIDTH ||
		vPos.y < 0 || vPos.y > WINDOW_HEIGHT) {
		Destroy();
	}

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
		fyDest = fx * sinTheta + fy * cosTheta;
		tPoint[i].x = fxDest + vPos.x;
		tPoint[i].y = fyDest + vPos.y;
	}

	POINT resolusion = Core::GetInst()->GetResolution();
	HDC tempDC = CreateCompatibleDC(_dc);
	HBITMAP tempBitmap = CreateCompatibleBitmap(_dc, resolusion.x, resolusion.y);
	SelectObject(tempDC, tempBitmap);

	BitBlt(
		tempDC,
		vPos.x - vScale.x / 2,
		vPos.y - vScale.y / 2,
		vScale.x,
		vScale.y,
		_dc,
		vPos.x - vScale.x / 2,
		vPos.y - vScale.y / 2,
		SRCCOPY
	);
	PlgBlt(tempDC,
		tPoint,
		m_pTex->GetDC(),
		0, 0, Width, Height,
		nullptr, 0, 0
	);
	TransparentBlt(
		_dc,
		vPos.x - vScale.x / 2,
		vPos.y - vScale.y / 2,
		vScale.x,
		vScale.y,
		tempDC,
		vPos.x - vScale.x / 2,
		vPos.y - vScale.y / 2,
		vScale.x,
		vScale.y,
		RGB(255, 0, 255)
	);
	
	Component_Render(_dc);

	DeleteDC(tempDC);
	DeleteObject(tempBitmap);
}

void Bullet::EnterCollision(Collider* _pOther)
{
	if (m_ownerObjectGroup == OBJECT_GROUP::PLAYER) {
		if (_pOther->GetObj()->GetName().rfind(L"Boss", 0) == 0) {
			((Boss*)_pOther->GetObj())->OnDamage(m_damage);
			Destroy();
		}
	}
	else if (m_ownerObjectGroup == OBJECT_GROUP::MONSTER) {
		if (_pOther->GetObj()->GetName() == L"Player") {
			((Player*)_pOther->GetObj())->OnDamage(m_damage);
			Destroy();
		}
	}
}

void Bullet::Destroy()
{
	GenerateDestroyParticle();
	EventMgr::GetInst()->DeleteObject(this);
}

void Bullet::GenerateDestroyParticle()
{
	Particle* particle = new Particle(PARTICLE_TYPE::BULLET_DESTROY, 0.05f, false);
	particle->SetPos(GetPos());
	particle->SetScale(Vec2(60, 60));
	SceneMgr::GetInst()->GetCurScene()->AddObject(particle, OBJECT_GROUP::PARTICLE);
}
