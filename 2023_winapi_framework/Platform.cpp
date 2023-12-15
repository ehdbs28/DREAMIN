#include "pch.h"
#include "Platform.h"
#include "Collider.h"
#include "Bullet.h"

Platform::Platform()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT / 5.f));
}

Platform::~Platform()
{
}

void Platform::Update()
{
}

void Platform::Render(HDC _dc)
{
	HBRUSH brush = CreateSolidBrush(BLACK_BRUSH);
	HBRUSH prevBrush = (HBRUSH)SelectObject(_dc, brush);

	Vec2 pos = GetPos();
	Vec2 scale = GetScale();

	RECT_RENDER(pos.x, pos.y, scale.x, scale.y, _dc);

	SelectObject(_dc, prevBrush);
	DeleteObject(brush);
}

void Platform::EnterCollision(Collider* _pOther)
{
	if (_pOther->GetObj()->GetName().rfind(L"Bullet", 0) == 0) {
		((Bullet*)_pOther->GetObj())->Destroy();
	}
}
