#include "pch.h"
#include "UIManager.h"
#include "UIPanel.h"
#include "TitleScreen.h"
#include "HowToPlayScreen.h"
#include "CreditsScreen.h"

void UIManager::Init()
{
	UIManager::GetInst()->AddPanel(L"TitleScreen", std::make_shared<TitleScreen>());
	UIManager::GetInst()->AddPanel(L"HowToPlay", std::make_shared<HowToPlayScreen>());
	UIManager::GetInst()->AddPanel(L"Credits", std::make_shared<CreditsScreen>());

	UIManager::GetInst()->LoadPanel(L"TitleScreen");
}

void UIManager::Update()
{
	std::shared_ptr<UIPanel> topPanel = GetTopPanel();
	if (topPanel != nullptr) {
		topPanel->Update();
	}
}

void UIManager::Render(HDC _dc)
{
	std::shared_ptr<UIPanel> topPanel = GetTopPanel();
	if (topPanel != nullptr) {
		topPanel->Render(_dc);
	}
}

void UIManager::AddPanel(wstring _key, std::shared_ptr<UIPanel> _panel)
{
	m_mapPanels.insert({ _key, _panel });
}

void UIManager::LoadPanel(wstring _key)
{
	std::shared_ptr<UIPanel> panel = GetTopPanel();

	if (panel != nullptr) {
		panel->Release();
	}

	panel = m_mapPanels[_key];

	if (panel != nullptr) {
		panel->Init();
		m_panelStack.push(panel);
	}
}

void UIManager::ReturnUI()
{
	if (m_panelStack.size() < 2) {
		return;
	}
	
	std::shared_ptr<UIPanel> panel = GetTopPanel();
	m_panelStack.pop();
	panel->Release();

	panel = GetTopPanel();
	panel->Init();
}

std::shared_ptr<UIPanel> UIManager::GetTopPanel()
{
	std::shared_ptr<UIPanel> panel = nullptr;
	if (m_panelStack.empty()) {
		panel = nullptr;
	}
	else {
		panel = m_panelStack.top();
	}
	return panel;
}
