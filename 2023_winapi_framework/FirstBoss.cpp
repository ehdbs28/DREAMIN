#include "pch.h"
#include "FirstBoss.h"
#include "BossPatternModule.h"
#include "ModuleController.h"
#include "Animator.h"
#include "ResMgr.h"
#include "LaserPattern.h"
#include "MovementPattern.h"
#include "BossLaserAroundPattern.h"

FirstBoss::FirstBoss()
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Boss1", L"Texture\\Boss1.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnim(L"Idle", m_pTex, Vec2(0, 0),
		Vec2(16, 16), Vec2(16, 0), 1, 0.2f);
	GetAnimator()->CreateAnim(L"Damaged", m_pTex, Vec2(0, 16),
		Vec2(16, 16), Vec2(16, 0), 2, 0.05f);
	GetAnimator()->PlayAnim(L"Idle", false);

	BossPatternModule* patternModule = (BossPatternModule*)m_pModuleController->GetModule(L"PatternModule");
	patternModule->AddPattern(new LaserPattern(m_pModuleController));
	patternModule->AddPattern(new MovementPattern(m_pModuleController));
	patternModule->AddPattern(new BossLaserAroundPattern(m_pModuleController));
}

FirstBoss::~FirstBoss()
{
}
