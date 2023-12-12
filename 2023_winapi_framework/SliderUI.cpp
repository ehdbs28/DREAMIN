#include "pch.h"
#include "SliderUI.h"
#include "ImageUI.h"
#include "ResMgr.h"

SliderUI::SliderUI()
	: m_backImage(nullptr)
	, m_innerImage(nullptr)
	, m_percent(1.f)
{
	m_backImage = new ImageUI;
	m_innerImage = new ImageUI;
}

SliderUI::~SliderUI()
{
	delete m_backImage;
	delete m_innerImage;
}

void SliderUI::Update()
{
}

void SliderUI::Render(HDC _dc)
{
	m_backImage->Render(_dc);
	m_innerImage->Render(_dc);
}

void SliderUI::SetPos(Vec2 _vPos)
{
	UIObject::SetPos(_vPos);
	m_backImage->SetPos(_vPos);
	m_innerImage->SetPos(_vPos + Vec2(1.5f, 1.5f));
}

void SliderUI::SetScale(Vec2 _vScale)
{
	UIObject::SetScale(_vScale);
	m_backImage->SetScale(_vScale);
	m_innerImage->SetScale(_vScale - Vec2(3, 3));
}

void SliderUI::SetPercent(float _percent)
{
	float maxWidth = GetScale().x - 7.f;
	Vec2 vScale = m_innerImage->GetScale();
	vScale.x = maxWidth * _percent;
	m_innerImage->SetScale(vScale);
}

void SliderUI::SetBackImage(wstring _name)
{
	m_backImage->SetTexture(_name);
}

void SliderUI::SetInnerImage(wstring _name)
{
	m_innerImage->SetTexture(_name);
}
