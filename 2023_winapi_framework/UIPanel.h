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

public:
	void AddObject(UIObject* _uiObj);

private:
	vector<UIObject*> m_vecUIObjs;

};

