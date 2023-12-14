#include "pch.h"
#include "FirstBoss.h"
#include "BossPatternModule.h"
#include "ModuleController.h"
#include "Animator.h"
#include "ResMgr.h"
#include "LaserPattern.h"
#include "MovementPattern.h"

FirstBoss::FirstBoss()
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Boss1", L"Texture\\Boss1.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnim(L"Boss1_Idle", m_pTex, Vec2(0, 0),
		Vec2(16, 16), Vec2(16, 0), 1, 0.2f);
	GetAnimator()->PlayAnim(L"Boss1_Idle", true);

	BossPatternModule* patternModule = (BossPatternModule*)m_pModuleController->GetModule(L"PatternModule");
	//patternModule->AddPattern(new LaserPattern(m_pModuleController));
	patternModule->AddPattern(new MovementPattern(m_pModuleController));
}

FirstBoss::~FirstBoss()
{
}
