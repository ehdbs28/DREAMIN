#include "pch.h"
#include "CameraManager.h"
#include "TimeMgr.h"

void CameraManager::Init(Vec2 _centerPos)
{
	m_centerPos = _centerPos;
	m_shakingPos = m_centerPos;
	m_isShaking = false;
}

void CameraManager::Update()
{
	if (m_isShaking) {
		m_durationTimer += fDT;
		m_shakingPos.x = m_centerPos.x + (rand() % m_shakeIntensity - 10);
		m_shakingPos.y = m_centerPos.y + (rand() % m_shakeIntensity - 10);

		if (m_durationTimer >= m_shakeDuration) {
			m_isShaking = false;
			m_shakingPos = m_centerPos;
		}
	}
}

void CameraManager::Shake(int _intensity, float _duration)
{
	m_isShaking = true;
	m_shakeDuration = _duration;
	m_shakeIntensity = _intensity;
	m_durationTimer = 0.f;
}
