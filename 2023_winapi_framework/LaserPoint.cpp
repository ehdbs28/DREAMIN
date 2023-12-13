#include "pch.h"
#include "LaserPoint.h"
#include "ResMgr.h"
#include "Animator.h"

LaserPoint::LaserPoint()
	: m_pTex(nullptr)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"LaserPoint", L"Texture\\LaserPoint.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnim(L"Idle", m_pTex, Vec2(0, 0), Vec2(16, 16), Vec2(16, 0), 2, 0.1f);
	GetAnimator()->PlayAnim(L"Idle", true);

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
