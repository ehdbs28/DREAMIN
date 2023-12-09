#pragma once
class Object;
struct tEvent
{
	EVENT_TYPE eEve; // �̺�Ʈ Ÿ��
	Object* Obj;
	OBJECT_GROUP ObjType;

public:
	friend bool operator == (const tEvent& _a, const tEvent& _b) {
		return _a.eEve == _b.eEve && _a.Obj == _b.Obj;
	}
};

class EventMgr
{
	SINGLE(EventMgr);
public:
	void Update();
	void DeleteObject(Object* _pObj);
private:
	void Excute(const tEvent& _eve);
private:
	vector<tEvent> m_vecEvent;
	vector<Object*> m_vecDead;
};

