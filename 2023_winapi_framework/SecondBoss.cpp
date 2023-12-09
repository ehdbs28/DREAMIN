#include "pch.h"
#include "SecondBoss.h"
#include "BossPatternModule.h"
#include "ModuleController.h"
#include "Animator.h"
#include "ResMgr.h"

SecondBoss::SecondBoss()
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Boss2", L"Texture\\Boss2.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnim(L"Boss2_Idle", m_pTex, Vec2(0, 0),
		Vec2(16, 16), Vec2(16, 0), 1, 0.2f);
	GetAnimator()->PlayAnim(L"Boss2_Idle", true);

	BossPatternModule* patternModule = (BossPatternModule*)m_pModuleController->GetModule(L"PatternModule");
	//patternModule->AddPattern()
}

SecondBoss::~SecondBoss()
{
}
