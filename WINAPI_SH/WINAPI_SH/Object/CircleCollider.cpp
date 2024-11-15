#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(Vector2D centre, float radius)
	: _centre(centre), _radius(radius)
{
}

void CircleCollider::Render(HDC hdc)
{
	int left = _centre.x - _radius;
	int top = _centre.y - _radius;
	int right = _centre.x + _radius;
	int bottom = _centre.y + _radius;

	Ellipse(hdc, left, top, right, bottom);
}