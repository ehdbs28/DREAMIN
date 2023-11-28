#pragma once
#include "BaseModule.h"

class PlayerMovementModule : public BaseModule
{
public:
	PlayerMovementModule(ModuleController* _controller);
	virtual ~PlayerMovementModule() override;

public:
	virtual void UpdateModule() override;

public:
	void SetGround(bool _val) { m_isGround = _val; }

public:
	const bool& GetGround() const { return m_isGround; }
	const Vec2& GetFrontDir() const { return m_frontDir; }

private:
	void SetInputValue();
	void CalcMovement();

private:
	float m_fGravity;
	
	float m_fMovementSpeed;
	float m_fJumpPower;

	Vec2 m_inputDir;
	Vec2 m_movementVelocity;
	Vec2 m_verticalVelocity;

	Vec2 m_frontDir;

	bool m_isGround;

};

