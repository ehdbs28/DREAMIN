#pragma once
#include "UIObject.h"

class Texture;

class ImageUI
	: public UIObject
{
public:
	ImageUI();
	~ImageUI();

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

public:
	void SetTexture(wstring& _key);

private:
	Texture* m_pTex;

};

