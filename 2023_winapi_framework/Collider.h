#pragma once
class Object;

class Collider
{
public:
	Collider();
	Collider(const Collider& _origin);
	~Collider();
	Collider& operator = (Collider& _origin) = delete;
public:
	void FinalUpdate();
	void Render(HDC _dc);
public:
	void EnterCollision(Collider* _pOther);
	void ExitCollision(Collider* _pOther);
	void StayCollision(Collider* _pOther);
public:
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }
	void SetOffSetPos(Vec2 _vOffsetPos) 
	{ m_vOffsetPos = _vOffsetPos; }
	const Vec2& GetScale() const { return m_vScale; }
	const Vec2& GetOffSetPos() const { return m_vOffsetPos; }
	const Vec2& GetFinalPos() const 
	{ return m_vFinalPos; }
	const UINT& GetID() const { return m_ID; }
	const Object* GetObj() const { return m_pOwner; }
private:
	UINT m_check;
	Object* m_pOwner;
	Vec2 m_vOffsetPos; // ������
	Vec2 m_vFinalPos; // ���̳� ��ġ
	Vec2 m_vScale; // ũ��
	friend class Object;
	UINT m_ID; // �浹ü ID��
	static UINT m_sNextID;
};

