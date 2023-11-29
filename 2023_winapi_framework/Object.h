#pragma once
class Collider;
class Animator;
class Rigidbody;

class Object
{
public:
	Object();
	virtual ~Object();
//public:	// 크기, 위치
	//POINT m_ptPos;
	//POINT m_ptScale;
public:
	virtual void Update() abstract;
	virtual void FinalUpdate() final;
	virtual void Render(HDC _dc) abstract;
	virtual void EnterCollision(Collider* _pOther);
	virtual void ExitCollision(Collider* _pOther);
	virtual void StayCollision(Collider* _pOther);
	void Component_Render(HDC _dc);
public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetAngle(float _angle) { m_fAngle = _angle; }
	const Vec2& GetPos() const { return m_vPos; }
	const Vec2& GetScale() const { return m_vScale; }
	const float& GetAngle() const { return m_fAngle; }
	Collider* GetCollider() { return m_pCollider; }
	Animator* GetAnimator() { return m_pAnimator; }
	Rigidbody* GetRigidbody() { return m_pRigidbody; }
	const wstring& GetName() const { return m_strName; }
	void SetName(wstring _name) { m_strName = _name; }
	bool GetIsDead() const { return !m_IsAlive; }
private:
	void SetDead() { m_IsAlive = false; }
	friend class EventMgr;
public:
	void CreateCollider();
	void CreateAnimator();
	void CreateRigidbody();
private:
	Vec2 m_vPos; // 위치
	Vec2 m_vScale; // 크기
	float m_fAngle;
	Collider* m_pCollider;
	wstring m_strName; // 이름.
	bool m_IsAlive;
	Animator* m_pAnimator;
	Rigidbody* m_pRigidbody;
};

