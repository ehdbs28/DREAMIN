#pragma once
#include "BossPattern.h"
class LaserPattern
	: BossPattern
{
public:
	LaserPattern(ModuleController* _controller);
	virtual ~LaserPattern();

public:
	virtual void ExcutePattern() override;

private:
	void CreateBullet();
private:
	Vec2 m_attackPoint;
	Vec2 m_attackDir;

	float m_fAttackDelayTimer;
	float m_fAttackDelay;

	float m_fDamage;
};
