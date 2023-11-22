#pragma once
class Collider;
union COLLIDER_ID
{
	struct
	{
		UINT left_ID;
		UINT right_ID;
	};
	ULONGLONG ID;
};
class CollisionMgr
{
	SINGLE(CollisionMgr);
public:
	void Update();
	void CheckGroup(OBJECT_GROUP _eLeft, OBJECT_GROUP _eRight);
	void CheckReset();
private:
	void CollisionGroupUpdate(OBJECT_GROUP _eLeft, OBJECT_GROUP _eRight);
	bool IsCollision(Collider* _pLeft, Collider* _pRight);
private:
	// �׷찣�� �浹üũ�� �迭
	UINT m_arrCheck[(UINT)OBJECT_GROUP::END];
	map<ULONGLONG, bool> m_mapColInfo;
};

