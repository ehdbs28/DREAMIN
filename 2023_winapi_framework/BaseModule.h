#pragma once

class ModuleController;

class BaseModule
{
public:
	BaseModule(ModuleController* _controller);
	virtual ~BaseModule();

public:
	virtual void UpdateModule() abstract;

protected:
	ModuleController*		m_pController;

};

