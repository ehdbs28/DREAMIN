#pragma once
class CameraManager
{
	SINGLE(CameraManager)

public:
	void Init(Vec2 _centerPos);
	void Update();

public:
	void Shake(int _intensity, float _duration);

public:
	const bool& IsShaking() const { return m_isShaking; }
	const Vec2& GetCenter() const { return m_centerPos; }
	const Vec2& GetShakingPos() const { return m_shakingPos;  }

private:
	Vec2 m_centerPos;
	Vec2 m_shakingPos;

	int m_shakeIntensity;
	float m_durationTimer;
	float m_shakeDuration;

	bool m_isShaking;

};

