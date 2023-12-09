#include "pch.h"
#include "NextStagePortal.h"
#include "Texture.h"
#include "ResMgr.h"
#include "Animation.h"
#include "Animator.h"
#include "Collider.h"

NextStagePortal::NextStagePortal()
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"NextStagePortal", L"Texture\\NextStagePortal.bmp");

	CreateCollider();
	GetCollider()->SetScale(Vec2(70, 100));

	CreateAnimator();
	GetAnimator()->CreateAnim(L"Open", m_pTex, Vec2(0, 0), Vec2(16, 16), Vec2(16, 0), 5, 0.05f);
	GetAnimator()->PlayAnim(L"Open", false);
}

NextStagePortal::~NextStagePortal()
{
}

void NextStagePortal::Update()
{
	GetAnimator()->Update();
}

void NextStagePortal::Render(HDC _dc)
{
	Component_Render(_dc);
}
