#include "pch.h"
#include "LaserPoint.h"
#include "ResMgr.h"
#include "Animator.h"
#include "Texture.h"

LaserPoint::LaserPoint()
	: m_pTex(nullptr)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"LaserPoint", L"Texture\\LaserPoint.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnim(L"Idle", m_pTex, Vec2(0, 0), Vec2(16, 16), Vec2(16, 0), 3, 0.1f);
	GetAnimator()->PlayAnim(L"Idle", false);
}

LaserPoint::~LaserPoint()
{
}

void LaserPoint::Update()
{
	GetAnimator()->Update();
}

void LaserPoint::Render(HDC _dc)
{
	//Vec2 vPos = GetPos();
	//Vec2 vScale = GetScale();
	//TransparentBlt(_dc,
	//	vPos.x, vPos.y, vScale.x, vScale.y,
	//	m_pTex->GetDC(),
	//	0, 0, m_pTex->GetWidth(), m_pTex->GetHeight(),
	//	RGB(255, 0, 255));
	Component_Render(_dc);
}
