#include "pch.h"
#include "BossPattern.h"

BossPattern::BossPattern(ModuleController* _controller)
	: m_pModuleController(_controller)
	, m_isExecute(false)
	, m_patternDuration(0.f)
	, m_patternDurationTimer(0.f)
{
}

BossPattern::~BossPattern()
{
}
