#include "pch.h"
#include "UIPanel.h"
#include "UIObject.h"

UIPanel::UIPanel()
{
}

UIPanel::~UIPanel()
{
	for (auto& obj : m_vecUIObjs) {
		delete obj;
	}
	m_vecUIObjs.clear();
}

void UIPanel::Update()
{
	for (auto& obj : m_vecUIObjs) {
		obj->Update();
	}
}

void UIPanel::Render(HDC _dc)
{
	for (auto& obj : m_vecUIObjs) {
		obj->Render(_dc);
	}
}

void UIPanel::Release()
{
	RemoveObjectAll();
}

void UIPanel::AddObject(UIObject* _uiObj)
{
	m_vecUIObjs.push_back(_uiObj);
}

void UIPanel::RemoveObject(UIObject* _uiObj)
{
	auto iter = std::find(m_vecUIObjs.begin(), m_vecUIObjs.end(), _uiObj);
	delete *iter;
	m_vecUIObjs.erase(iter);
}

void UIPanel::RemoveObjectAll()
{
	for (auto& obj : m_vecUIObjs) {
		delete obj;
	}
	m_vecUIObjs.clear();
}
