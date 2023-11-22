#pragma once
class Texture; class Animator;
struct tAnimFrame
{
	Vec2 vLT;
	Vec2 vSlice;
	float fDuration;
	Vec2 vOffset;
};

class Animation
{
public:
	Animation();
	~Animation();
public:
	void Update();
	void Render(HDC _dc);
public:
	void Create(Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, 
		Vec2 _vStep, int _framecount, float _fDuration);
public:
	const wstring& GetName() const { return m_strName; }
	void SetName(wstring _name) { m_strName = _name; }
	void SetFrameOffset(int _index, Vec2 _offset) { m_vecAnimFrame[_index].vOffset = _offset; }
	const size_t& GetMaxFrame() { return m_vecAnimFrame.size(); }
	friend class Animator;
private:
	UINT   m_CurFrame; // 현재 프레임
	float  m_fAccTime; // 누적 시간
	int	   m_repeatcnt; // 반복 횟수
	Texture* m_pTex; // 애니메이션 텍스처
	vector<tAnimFrame> m_vecAnimFrame;
	wstring m_strName;
	Animator* m_pAnimator;

};

