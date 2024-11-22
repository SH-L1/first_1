#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(Vector2D centre, float radius)
	: _centre(centre), _radius(radius)
{
}

void CircleCollider::Update()
{
	// 마우스 포인터를 향해서 등속운동하는 방법
	/* Vector2D direction = (mousePos - _centre).NormalVector();

	if (direction.Length() < 10) return;
	
	direction = direction.NormalVector();
	_centre = _centre + direction * 10.0f; */

	// 보간을 이용해서 부드럽게 움직이는 방법
	// Linear Interporation
	_centre = (mousePos - _centre) * 0.01f + _centre;
}

void CircleCollider::Render(HDC hdc)
{
	int left = _centre.x - _radius;
	int top = _centre.y - _radius;
	int right = _centre.x + _radius;
	int bottom = _centre.y + _radius;

	Ellipse(hdc, left, top, right, bottom);
}