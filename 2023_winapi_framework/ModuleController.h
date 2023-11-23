#pragma once

class BaseModule;

class ModuleController
{
public:
	ModuleController();
	~ModuleController();

public:
	void Update();

public:
	void AddModule(BaseModule* _module);

private:
	std::vector<BaseModule*> m_vecModule;

};

