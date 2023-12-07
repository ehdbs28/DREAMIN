#pragma once
#include "Object.h"

class Texture;
class ModuleController;
class Player;

class Boss
	: public Object
{
public:
	Boss();
	virtual ~Boss();

public:
	virtual void Update() override;
	virtual void Render(HDC _dc) override;

public:
	const Player* GetTarget() const { return m_pTarget; }

protected:
	Player* m_pTarget;

	Texture* m_pTex;
	ModuleController* m_pModuleController;

};

