#pragma once
class Object;
class Texture;
class Animation;
class Animator
{
public:
	Animator();
	~Animator();
public:
	void Update();
	void Render(HDC _dc);
public:
	// 애니메이션 생성함수
	void CreateAnim(const wstring& _strName, Texture* _pTex,
					Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep,
					UINT _framecount, float _fDuration);
	// 애니메이션 찾기함수
	Animation* FindAnim(const wstring& _strName);

	// 애니메이션 플레이 함수
	void PlayAnim(const wstring& _strName, bool _bRepeat, int _repeatcnt = 1);
public:
	Object* GetObj() const { return m_pOwner; }
	const bool& GetRepeat() const { return m_IsRepeat; }
	const int& GetRepeatcnt() const { return m_repeatcnt; }
	void SetRepeatcnt() { --m_repeatcnt; }
private:
	map<wstring, Animation*> m_mapAnim;
	Animation* m_pCurAnim;
	Object* m_pOwner;
	friend class Object;
	bool	m_IsRepeat;
	int		m_repeatcnt;
};

