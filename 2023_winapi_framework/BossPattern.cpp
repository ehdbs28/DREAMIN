#include "pch.h"
#include "BossPattern.h"

BossPattern::BossPattern(ModuleController* _controller)
	: m_pModuleController(_controller)
	, m_isExecute(false)
{
}

BossPattern::~BossPattern()
{
}
