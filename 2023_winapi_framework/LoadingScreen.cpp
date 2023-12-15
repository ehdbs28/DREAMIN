#include "pch.h"
#include "LoadingScreen.h"
#include "Texture.h"
#include "TimeMgr.h"
#include "Animator.h"
#include "ResMgr.h"
#include "Animation.h"

LoadingScreen::LoadingScreen()
	: m_pTex(nullptr)
	, m_isComplete(false)
	, m_currentTime(0.f)
	, m_loadingDelay(0.f)
{
	m_pTex = ResMgr::GetInst()->TexLoad(L"LoadingScreen", L"Texture\\UI\\LoadingScreen.bmp");

	CreateAnimator();
	GetAnimator()->CreateAnim(L"LoadOn", m_pTex, Vec2(0, 0), Vec2(16, 16), Vec2(16, 0), 16, 0.025f);
	GetAnimator()->CreateAnim(L"LoadOff", m_pTex, Vec2(0, 16), Vec2(16, 16), Vec2(16, 0), 17, 0.025f);
}

LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::Loading(bool _loadOn)
{
	m_loadOn = _loadOn;
	m_currentTime = 0.f;
	m_isComplete = false;
	if (_loadOn) {
		GetAnimator()->PlayAnim(L"LoadOn", false);
	}
	else {
		GetAnimator()->PlayAnim(L"LoadOff", false);
	}
}

void LoadingScreen::Update()
{
	GetAnimator()->Update();
	if (GetAnimator()->GetCurAnim()->GetCurFrame() + 1 == GetAnimator()->GetCurAnim()->GetMaxFrame()) {
		if (m_loadOn) {
			m_currentTime += fDT;
			if (m_currentTime < m_loadingDelay) {
				return;
			}
		}
		m_isComplete = true;
	}
}

void LoadingScreen::Render(HDC _dc)
{
	Component_Render(_dc);
}