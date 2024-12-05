#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector2D centre, Vector2D size)
	: _halfSize(size * 0.5f)
{
	_centre = centre;
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
}

void RectCollider::Render(HDC hdc)
{
	SelectObject(hdc, _pens[_curColor]);

	Rectangle(hdc, Left(), Top(), Right(), Bottom());
}
