#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector2D centre, Vector2D size)
	: _centre(centre), _size(size)
{
}

void RectCollider::Render(HDC hdc)
{
	int left = _centre.x - (_size.x / 2.0f);
	int top = _centre.y - (_size.y / 2.0f);
	int right = _centre.x + (_size.x / 2.0f);
	int bottom = _centre.y + (_size.y / 2.f);

	Rectangle(hdc, left, top, right, bottom);
}
