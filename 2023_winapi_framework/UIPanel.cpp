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

void UIPanel::AddObject(UIObject* _uiObj)
{
	m_vecUIObjs.push_back(_uiObj);
}
