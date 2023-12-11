#include "pch.h"
#include "UIMenuSystem.h"
#include "UIMenu.h"
#include "KeyMgr.h"
#include "UIPanel.h"

UIMenuSystem::UIMenuSystem()
	: m_selectIndex(0)
	, m_padding(40)
{
}

UIMenuSystem::~UIMenuSystem()
{
	for (auto& menu : m_vecMenus) {
		delete menu;
	}
	m_vecMenus.clear();
}

void UIMenuSystem::Update()
{
	if (KEY_DOWN(KEY_TYPE::UP)) {
		MenuUpHandle();
	}
	if (KEY_DOWN(KEY_TYPE::DOWN)) {
		MenuDownHandle();
	}
	if (KEY_DOWN(KEY_TYPE::ENTER)) {
		EnterHandle();
	}

	for (int i = 0; i < m_vecMenus.size(); i++) {
		m_vecMenus[i]->Update();
		m_vecMenus[i]->SetSelected(i == m_selectIndex);
	}
}

void UIMenuSystem::Render(HDC _dc)
{
	for (auto& menu : m_vecMenus) {
		menu->Render(_dc);
	}
}

void UIMenuSystem::AddMenu(UIMenu* _menu, wstring _name, void(*_enterEvent)())
{
	Vec2 vPos = GetPos();
	_menu->Init(vPos + Vec2(0, m_vecMenus.size() * m_padding), _name, _enterEvent);
	m_vecMenus.push_back(_menu);
}

void UIMenuSystem::MenuUpHandle()
{
	if (m_selectIndex <= 0) {
		return;
	}
	--m_selectIndex;
}

void UIMenuSystem::MenuDownHandle()
{
	if (m_selectIndex >= m_vecMenus.size()) {
		return;
	}
	++m_selectIndex;
}

void UIMenuSystem::EnterHandle()
{
	m_vecMenus[m_selectIndex]->OnEnter();
}
