#pragma once

class ModuleController;

class BossPattern
{
public:
	BossPattern(ModuleController* _controller);
	virtual ~BossPattern();

public:
	virtual void ExcutePattern() abstract;

public:
	const bool& IsExcute() const { return m_isExecute; }

protected:
	ModuleController* m_pModuleController;
	bool m_isExecute;

	float m_patternDuration;
	float m_patternDurationTimer;

};

