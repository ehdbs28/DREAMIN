#pragma once

class ModuleController;

class BaseModule
{
public:
	BaseModule();
	virtual ~BaseModule();

public:
	virtual void UpdateModule() abstract;

private:
	ModuleController*		m_pController;
	friend class ModuleController;

};

