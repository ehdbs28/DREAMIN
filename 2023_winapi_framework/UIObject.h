#pragma once

class UIObject
{
public:
	UIObject();
	virtual ~UIObject();

public:
	virtual void Update() abstract;
	virtual void Render(HDC _dc) abstract;

public:
	const Vec2& GetPos() const { return m_vPos; }
	const Vec2& GetScale() const { return m_vScale; }

public:
	virtual void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	virtual void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

private:
	Vec2 m_vPos;
	Vec2 m_vScale;

};

