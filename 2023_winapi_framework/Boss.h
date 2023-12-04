#pragma once
#include "Object.h"

class Texture;
class ModuleController;

class Boss
	: public Object
{
public:
	Boss();
	~Boss();

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

protected:
	Texture* m_pTex;
	ModuleController* m_pModuleController;

};

