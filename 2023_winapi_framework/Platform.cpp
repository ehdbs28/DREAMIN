#include "pch.h"
#include "Platform.h"
#include "Collider.h"

Platform::Platform()
{
	CreateCollider();
	GetCollider()->SetScale(Vec2((float)WINDOW_WIDTH, (float)WINDOW_HEIGHT / 6.f));
}

Platform::~Platform()
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
