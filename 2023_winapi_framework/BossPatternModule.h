#pragma once
#pragma once
#include "BaseModule.h"

class BossPattern;

class BossPatternModule
	: public BaseModule
{
public:
	BossPatternModule(ModuleController* _controller);
	virtual ~BossPatternModule();

public:
	virtual void EnterModule() override;
	virtual void UpdateModule() override;
	virtual void ExitModule() override;

public:
	void AddModule(BossPattern* _newPattern);

private:
	void SelectPattern();
	void ShufflePatternOrder();

private:
	vector<BossPattern*> m_vecPattern;
	BossPattern* m_currentPattern;

	vector<int> m_vecOrder;
	int m_patternIndex;

};

