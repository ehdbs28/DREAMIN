#include "pch.h"
#include "UIMenu.h"
#include "ImageUI.h"
#include "TextUI.h"
#include "UIPanel.h"

UIMenu::UIMenu()
	: m_isSelected(false)
	, onEnterEvent(nullptr)
	, m_pImage(nullptr)
	, m_pText(nullptr)
{
}

UIMenu::~UIMenu()
{
	delete m_pImage;
	delete m_pText;
}

void UIMenu::Init(Vec2 _vPos, wstring& _name, std::function<void()> _enterEvent)
{
	m_pImage = new ImageUI();
	m_pImage->SetPos(_vPos);
	m_pImage->SetScale(Vec2(25, 25));

	m_pText = new TextUI;
	m_pText->SetPos(_vPos + Vec2(40, 0));
	m_pText->SetText(_name);
	m_pText->SetSize(25);

	onEnterEvent = _enterEvent;
}

void UIMenu::Update()
{
}

void UIMenu::Render(HDC _dc)
{
	if (m_pImage != nullptr)
		m_pImage->Render(_dc);
	if (m_pText != nullptr)
		m_pText->Render(_dc);
}

void UIMenu::OnEnter()
{
	if (onEnterEvent != nullptr) {
		onEnterEvent();
	}
}

void UIMenu::SetSelected(bool _selected)
{
	m_isSelected = _selected;
	wstring key = m_isSelected ? L"SelectedBox" : L"UnSelectedBox";
	m_pImage->SetTexture(key);
}
