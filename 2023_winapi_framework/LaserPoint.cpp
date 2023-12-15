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
	GetAnimator()->CreateAnim(L"Shot", m_pTex, Vec2(0, 16), Vec2(16, 16), Vec2(16, 0), 3, 0.02f);
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
	Component_Render(_dc);
}
