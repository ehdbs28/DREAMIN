#include "pch.h"
#include "Platform.h"
#include "Collider.h"

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
	Component_Render(_dc);

	SelectObject(_dc, prevBrush);
	DeleteObject(brush);
}
