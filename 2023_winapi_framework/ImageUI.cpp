#include "pch.h"
#include "ImageUI.h"
#include "Texture.h"
#include "ResMgr.h"

ImageUI::ImageUI()
	: m_pTex(nullptr)
{
}

ImageUI::~ImageUI()
{
	m_pTex = nullptr;
}

void ImageUI::Update()
{
}

void ImageUI::Render(HDC _dc)
{
	if (m_pTex == nullptr) {
		return;
	}

	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	int width = m_pTex->GetWidth();
	int height = m_pTex->GetHeight();

	TransparentBlt(
		_dc,
		vPos.x, vPos.y,
		vScale.x, vScale.y,
		m_pTex->GetDC(), 0, 0, width, height,
		RGB(255, 0, 255)
	);
}

void ImageUI::SetTexture(wstring _key)
{
	m_pTex = ResMgr::GetInst()->TexLoad(_key, L"Texture\\UI\\" + _key + L".bmp");
}
