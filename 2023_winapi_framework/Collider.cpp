#include "pch.h"
#include "Collider.h"
#include "Object.h"
#include "SelectGDI.h"
UINT Collider::m_sNextID = 0;
Collider::Collider()
	: m_pOwner(nullptr)
	, m_vScale(Vec2(40.f,40.f))
	, m_ID(m_sNextID++)
	, m_check(0)
	, m_vFinalPos{}
{
	//Collider a, b;
	//a = b;
}

Collider::Collider(const Collider& _origin)
	: m_pOwner(nullptr)
	, m_vScale(_origin.m_vScale)
	, m_vOffsetPos(_origin.m_vOffsetPos)
	, m_ID(m_sNextID++)
	, m_check(0)
	, m_vFinalPos{}
{
}

Collider::~Collider()
{}

void Collider::Render(HDC _dc)
{
	//Core::GetInst()->GetPen(PEN_TYPE::GREEN);
	//Core::GetInst()->GetBrush(BRUSH_TYPE::HOLLOW);
	//SelectObject();
	PEN_TYPE ePen = PEN_TYPE::GREEN;
	if (m_check)
		ePen = PEN_TYPE::RED;
	SelectGDI pen(_dc, ePen);
	SelectGDI brush(_dc, BRUSH_TYPE::HOLLOW);
	
	Object* pObj = GetObj();
	Vec2 vPos = m_vFinalPos;

	if (pObj->GetName() == L"Laser") {
		vPos = Vec2(pObj->GetPos().x - pObj->GetScale().x / 2 + 15, pObj->GetPos().y);
	}

	float angle = pObj->GetAngle();

	POINT tPoint[4] = { 0, };
	Vec2 pos[4] = {};
	float fxDest, fyDest;
	float fRadian = angle * (M_PI / 180.f);
	float cosTheta = cosf(fRadian);
	float sinTheta = sinf(fRadian);

	if (pObj->GetName() == L"Laser") {
		pos[0] = Vec2(0.f, -m_vScale.y / 2.f);
		pos[1] = Vec2(m_vScale.x, -m_vScale.y / 2.f);
		pos[2] = Vec2(m_vScale.x, m_vScale.y / 2.f);
		pos[3] = Vec2(0.f, m_vScale.y / 2.f);
	}
	else {
		pos[0] = Vec2(-m_vScale.x / 2.f, -m_vScale.y / 2.f);
		pos[1] = Vec2(m_vScale.x / 2.f, -m_vScale.y / 2.f);
		pos[2] = Vec2(m_vScale.x / 2.f, m_vScale.y / 2.f);
		pos[3] = Vec2(-m_vScale.x / 2.f, m_vScale.y / 2.f);
	}

	for (int i = 0; i < 4; i++) {
		fxDest = pos[i].x * cosTheta - pos[i].y * sinTheta;
		fyDest = pos[i].x * sinTheta + pos[i].y * cosTheta;
		tPoint[i].x = fxDest + vPos.x;
		tPoint[i].y = fyDest + vPos.y;
	}

	Polygon(_dc, tPoint, 4);
}

void Collider::EnterCollision(Collider* _pOther)
{
 	++m_check;
	m_pOwner->EnterCollision(_pOther);
}

void Collider::ExitCollision(Collider* _pOther)
{
	--m_check;
	m_pOwner->ExitCollision(_pOther);
}

void Collider::StayCollision(Collider* _pOther)
{
	m_pOwner->StayCollision(_pOther);
}

Vec2 Collider::GetHeightVector()
{
	float fAngle = m_pOwner->GetAngle();
	float fRadian = fAngle * (M_PI / 180.0f);

	float cosTheta = cosf(fRadian);
	float sinTheta = sinf(fRadian);

	return Vec2(-m_vScale.y * 0.5f * sinTheta, m_vScale.y * 0.5f * cosTheta);
}

Vec2 Collider::GetWidthVector()
{
	float fAngle = m_pOwner->GetAngle();
	float fRadian = fAngle * (M_PI / 180.0f);

	float cosTheta = cosf(fRadian);
	float sinTheta = sinf(fRadian);

	return Vec2(m_vScale.x * 0.5f * cosTheta, m_vScale.x * 0.5f * sinTheta);
}

void Collider::FinalUpdate()
{
	// Object위치를 따라가야 하는거야.
	Vec2 vObjPos = m_pOwner->GetPos();
	m_vFinalPos = vObjPos + m_vOffsetPos;
}

