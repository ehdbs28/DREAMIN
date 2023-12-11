#pragma once
#include "UIObject.h"

class ImageUI;
class TextUI;

class UIMenu
	: public UIObject
{
public:
	UIMenu();
	~UIMenu();

public:
	void Init(Vec2 _vPos, wstring& _name, std::function<void()> _enterEvent);
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

public:
	void OnEnter();

public:
	void SetSelected(bool _selected);

private:
	std::function<void()> onEnterEvent;
	bool m_isSelected;

	ImageUI* m_pImage;
	TextUI* m_pText;

};

