#include "pch.h"
#include "Animation.h"
#include "Animator.h"
#include "Object.h"
#include "Texture.h"
#include "TimeMgr.h"
#include "Core.h"

Animation::Animation()
	: m_pAnimator(nullptr)
	, m_CurFrame(0)
	, m_pTex(nullptr)
	, m_fAccTime(0.f)
{
}

Animation::~Animation()
{
}

void Animation::Update()
{
	if (m_pAnimator->GetRepeatcnt() <= 0) {
		m_CurFrame = m_vecAnimFrame.size() - 1;
		return;
	}

	m_fAccTime += fDT;
	// 누적한 시간이 내가 이 프레임에 진행한 시간을 넘어섰냐?
	if (m_fAccTime >= m_vecAnimFrame[m_CurFrame].fDuration)
	{
		// 일단 모은 시간에서 현재 진행한 시간을 빼고
		m_fAccTime -= m_vecAnimFrame[m_CurFrame].fDuration;
		++m_CurFrame; // 다음프레임으로 옮기기
		if (m_CurFrame >= m_vecAnimFrame.size()) // 한바퀴 돌게하고싶어
		{
			if (!m_pAnimator->GetRepeat()) {
				m_pAnimator->SetRepeatcnt();
			}
			m_CurFrame = 0;
			m_fAccTime = 0.f;
		}
	}
}

void Animation::Render(HDC _dc)
{
	Object* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();
	Vec2 vScale = pObj->GetScale();

	if (pObj->GetName() == L"Laser") {
		vPos = Vec2(pObj->GetPos().x - pObj->GetScale().x / 2 + 15, pObj->GetPos().y);
	}

	if(!m_isRotate){
		// 오프셋 적용
		TransparentBlt(_dc
			,(int)(vPos.x - vScale.x /2.f)
			,(int)(vPos.y - vScale.y / 2.f)
			,(int)(vScale.x)
			,(int)(vScale.y)
			,m_pTex->GetDC()
			,(int)(m_vecAnimFrame[m_CurFrame].vLT.x)
			,(int)(m_vecAnimFrame[m_CurFrame].vLT.y)
			,(int)(m_vecAnimFrame[m_CurFrame].vSlice.x)
			,(int)(m_vecAnimFrame[m_CurFrame].vSlice.y)
			,RGB(255,0,255));
	}
	else {
		float angle = pObj->GetAngle();
		int Width = m_pTex->GetWidth();
		int Height = m_pTex->GetHeight();

		POINT tPoint[3] = { 0, };
		Vec2 pos[3] = {};
		float fxDest, fyDest;
		float fRadian = angle * (M_PI / 180.f);
		float cosTheta = cosf(fRadian);
		float sinTheta = sinf(fRadian);

		if (pObj->GetName() == L"Laser") {
			pos[0] = Vec2(0.f, -vScale.y / 2.f);
			pos[1] = Vec2(vScale.x, -vScale.y / 2.f);
			pos[2] = Vec2(0.f, vScale.y / 2.f);
		}
		else {
			pos[0] = Vec2(-vScale.x / 2.f, -vScale.y / 2.f);
			pos[1] = Vec2(vScale.x / 2.f, -vScale.y / 2.f);
			pos[2] = Vec2(-vScale.x / 2.f, vScale.y / 2.f);
		}

		for (int i = 0; i < 3; i++) {
			fxDest = pos[i].x * cosTheta - pos[i].y * sinTheta;
			fyDest = pos[i].x * sinTheta + pos[i].y * cosTheta;
			tPoint[i].x = fxDest + vPos.x;
			tPoint[i].y = fyDest + vPos.y;
		}

		POINT resolusion = Core::GetInst()->GetResolution();
		HDC tempDC = CreateCompatibleDC(_dc);
		HBITMAP tempBitmap = CreateCompatibleBitmap(_dc, resolusion.x, resolusion.y);
		SelectObject(tempDC, tempBitmap);

		// 물어볼부분
		Vec2 leftTop = Vec2(
			(int)min(tPoint[0].x, min(tPoint[1].x, tPoint[2].x)),
			(int)min(tPoint[0].y, min(tPoint[1].y, tPoint[2].y))
		);
		float width = abs(Vec2::Dot(Vec2(1, 0), (Vec2((int)tPoint[1].x, (int)tPoint[1].y) - Vec2((int)tPoint[0].x, (int)tPoint[0].y))))
					+ abs(Vec2::Dot(Vec2(1, 0), (Vec2((int)tPoint[2].x, (int)tPoint[2].y) - Vec2((int)tPoint[0].x, (int)tPoint[0].y))));
		float height = abs(Vec2::Dot(Vec2(0, 1), (Vec2((int)tPoint[1].x, (int)tPoint[1].y) - Vec2((int)tPoint[0].x, (int)tPoint[0].y))))
					 + abs(Vec2::Dot(Vec2(0, 1), (Vec2((int)tPoint[2].x, (int)tPoint[2].y) - Vec2((int)tPoint[0].x, (int)tPoint[0].y))));

		if (leftTop.x < 0) {
			leftTop.x = 0;
		}
		if (leftTop.y < 0) {
			leftTop.y = 0;
		}

		if (leftTop.x + width >= resolusion.x) {
			width -= leftTop.x + width - resolusion.x;
		}
		if (leftTop.y + height >= resolusion.y) {
			height -= leftTop.y + height - resolusion.y;
		}

		BitBlt(
			tempDC,
			leftTop.x,
			leftTop.y,
			width,
			height,
			_dc,
			leftTop.x,
			leftTop.y,
			SRCCOPY
		);
		PlgBlt(tempDC,
			tPoint,
			m_pTex->GetDC(),
			(int)(m_vecAnimFrame[m_CurFrame].vLT.x),
			(int)(m_vecAnimFrame[m_CurFrame].vLT.y),
			(int)(m_vecAnimFrame[m_CurFrame].vSlice.x),
			(int)(m_vecAnimFrame[m_CurFrame].vSlice.y),
			nullptr, 0, 0
		);
		TransparentBlt(
			_dc,
			leftTop.x, leftTop.y, width, height,
			tempDC,
			leftTop.x, leftTop.y, width, height,
			RGB(255, 0, 255)
		);
		
		DeleteDC(tempDC);
		DeleteObject(tempBitmap);
	}
}

void Animation::Create(Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, int _framecount, float _fDuration, bool _isRotate)
{
	m_pTex = _pTex;
	m_isRotate = _isRotate;
	for (int i = 0; i < _framecount; ++i)
	{
		m_vecAnimFrame.push_back(tAnimFrame({ _vLT + _vStep * i,
			_vSliceSize, _fDuration,{0.f,0.f} }));
	}

}
