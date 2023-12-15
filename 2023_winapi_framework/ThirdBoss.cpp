#include "pch.h"
#include "ThirdBoss.h"
#include "BossPatternModule.h"
#include "ModuleController.h"
#include "Animator.h"
#include "ResMgr.h"
#include "FollowBulletPattern.h"
#include "RadialBulletPattern.h"
#include "MovementPattern.h"
#include "CrossBulletPattern.h"

ThirdBoss::ThirdBoss()
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"Boss3", L"Texture\\Boss3.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnim(L"Idle", m_pTex, Vec2(0, 0),
		Vec2(16, 16), Vec2(16, 0), 1, 0.2f, true);
	GetAnimator()->CreateAnim(L"Damaged", m_pTex, Vec2(0, 16),
		Vec2(16, 16), Vec2(16, 0), 2, 0.05f, true);
	GetAnimator()->PlayAnim(L"Idle", false);

	BossPatternModule* patternModule = (BossPatternModule*)m_pModuleController->GetModule(L"PatternModule");
	patternModule->AddPattern(new CrossBulletPattern(m_pModuleController));
	patternModule->AddPattern(new RadialBulletPattern(m_pModuleController));
	patternModule->AddPattern(new FollowBulletPattern(m_pModuleController));
	patternModule->AddPattern(new MovementPattern(m_pModuleController));
}

ThirdBoss::~ThirdBoss()
{
}
