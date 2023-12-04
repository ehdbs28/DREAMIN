#pragma once
#include "BaseModule.h"

class PlayerMovementModule : public BaseModule
{
public:
	PlayerMovementModule(ModuleController* _controller);
	virtual ~PlayerMovementModule() override;

public:
	virtual void EnterModule() override;
	virtual void UpdateModule() override;
	virtual void ExitModule() override;

private:
	void SetInputValue();

private:
	float m_fMovementSpeed;
	Vec2 m_inputDir;

};

