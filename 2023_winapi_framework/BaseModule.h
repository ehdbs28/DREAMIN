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
	virtual void UpdateModule();
	virtual void ExitModule();

public:
	void SetAnimationKey(wstring _key);

public:
	const bool& GetActive() const { return m_active; }

protected:
	ModuleController*		m_pController;
	Rigidbody*				m_pRigidbody;
	Animator*				m_pAnimator;
	
	wstring					m_animationKey;

	bool m_active;

};

