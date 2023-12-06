#pragma once
#include "BossPattern.h"
class BulletPattern
	: BossPattern
{
public:
	BulletPattern(ModuleController* _controller);
	virtual ~BulletPattern();

public:
	virtual void ExcutePattern() override;
private:
	Vec2 m_attackPoint;
	Vec2 m_attackDir;

	float m_fAttackDelayTimer;
	float m_fAttackDelay;

	float m_fDamage;
};

