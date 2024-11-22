#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector2D centre, Vector2D size)
	: _centre(centre), _halfsize(size * 0.5f)
{
	_angle = 0;
}

RectCollider::~RectCollider()
{
}

void RectCollider::Update()
{
	_angle += 0.1f;

	_centre.x = 500 + 130 * cos(_angle);
	_centre.y = 500 + 130 * sin(-_angle);
}

void RectCollider::Render(HDC hdc)
{
	Rectangle(hdc, Left(), Top(), Right(), Bottom());
}
