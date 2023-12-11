#pragma once

class UIObject;

class UIPanel
{
public:
	UIPanel();
	virtual ~UIPanel();

public:
	virtual void Init() abstract;
	virtual void Update();
	virtual void Render(HDC _dc);
	virtual void Release();

public:
	void AddObject(UIObject* _uiObj);
	void RemoveObject(UIObject* _uiObj);
	void RemoveObjectAll();

private:
	vector<UIObject*> m_vecUIObjs;

};

