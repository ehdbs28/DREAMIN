#pragma once

class ModuleController;

class BaseModule
{
public:
	BaseModule(ModuleController* _controller);
	virtual ~BaseModule();

public:
	virtual void EnterModule() abstract;
	virtual void UpdateModule() abstract;
	virtual void ExitModule() abstract;

protected:
	ModuleController*		m_pController;

};

