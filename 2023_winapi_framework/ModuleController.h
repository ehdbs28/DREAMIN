#pragma once

class BaseModule;
class Object;

class ModuleController
{
public:
	ModuleController();
	~ModuleController();

public:
	void Update();

public:
	void AddModule(wstring _key, BaseModule* _module);
	void ChangeModule(wstring _key);

public:
	void SetOwner(Object* _owner) { m_pOwner = _owner; }

public:
	Object* GetOwner() const { return m_pOwner; }
	BaseModule* GetModule(wstring _key) const { return m_moduleMap.at(_key); }

private:
	Object* m_pOwner;

	std::map<wstring, BaseModule*> m_moduleMap;
	BaseModule* m_currentModule;

};

