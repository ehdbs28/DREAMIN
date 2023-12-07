#pragma once

class ModuleController;
class Rigidbody;
class Animator;

class BaseModule
{
public:
	BaseModule(ModuleController* _controller);
	virtual ~BaseModule();

public:
	virtual void EnterModule();
	virtual void UpdateModule() abstract;
	virtual void ExitModule();

public:
	const bool& GetActive() const { return m_active; }

protected:
	ModuleController*		m_pController;
	Rigidbody*				m_pRigidbody;
	Animator*				m_pAnimator;

	bool m_active;

};

