#pragma once

class UIPanel;

class UIManager
{
	SINGLE(UIManager)

public:
	void Update();
	void Render(HDC _dc);

public:
	void AddPanel(wstring _key, std::shared_ptr<UIPanel> _panel);
	void LoadPanel(wstring _key);
	void ReturnUI();

public:
	std::shared_ptr<UIPanel> GetTopPanel();

private:
	std::stack<std::shared_ptr<UIPanel>> m_panelStack;
	map<wstring, std::shared_ptr<UIPanel>> m_mapPanels;

};

