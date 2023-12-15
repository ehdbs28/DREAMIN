#include "pch.h"
#include "ThirdBoss.h"
#include "BossPatternModule.h"
#include "ModuleController.h"
#include "Animator.h"
#include "ResMgr.h"
#include "DownAttackPattern.h"
#include "VerticalWallPattern.h"
#include "HorizontalWallPattern.h"
#include "MovementPattern.h"

ThirdBoss::ThirdBoss()
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Boss2", L"Texture\\Boss3.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnim(L"Idle", m_pTex, Vec2(0, 0),
		Vec2(16, 16), Vec2(16, 0), 1, 0.2f, true);
	GetAnimator()->CreateAnim(L"Damaged", m_pTex, Vec2(0, 16),
		Vec2(16, 16), Vec2(16, 0), 2, 0.05f, true);
	GetAnimator()->PlayAnim(L"Idle", false);

	BossPatternModule* patternModule = (BossPatternModule*)m_pModuleController->GetModule(L"PatternModule");
	patternModule->AddPattern(new DownAttackPattern(m_pModuleController));
	patternModule->AddPattern(new MovementPattern(m_pModuleController));
	patternModule->AddPattern(new VerticalWallPattern(m_pModuleController));
	patternModule->AddPattern(new HorizontalWallPattern(m_pModuleController));
}

ThirdBoss::~ThirdBoss()
{
}
