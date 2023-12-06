#pragma once
#include "BaseModule.h"

class PlayerGroundModule
	: public BaseModule
{
public:
	PlayerGroundModule(ModuleController* _controller);
	virtual ~PlayerGroundModule();

public:
	virtual void UpdateModule() override;

};

