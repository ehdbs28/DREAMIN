#pragma once
#include "UIObject.h"
#include <vector>

class UIMenu;

class UIMenuSystem :
    public UIObject
{
public:
    UIMenuSystem();
    ~UIMenuSystem();

public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

public:
    void AddMenu(UIMenu* _menu, wstring _name, void(*_enterEvent)());

public:
    void MenuUpHandle();
    void MenuDownHandle();
    void EnterHandle();

private:
    int m_padding;

    int m_selectIndex;
    std::vector<UIMenu*> m_vecMenus;

};

