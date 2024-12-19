#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(Vector2D centre, float radius)
	: _radius(radius)
{
	this->centre = centre;
	_type = Collider::CIRCLE;
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
	// centre = (mousePos - centre) * 0.5f + centre;
}

void CircleCollider::Render(HDC hdc)
{
	SelectObject(hdc, _pens[_curColor]);

	int left = centre.x - _radius;
	int right = centre.x + _radius;
	int top = centre.y - _radius;
	int bottom = centre.y + _radius;
	Ellipse(hdc, left, top, right, bottom);
}

bool CircleCollider::IsCollision(const Vector2D& pos)
{
	return (pos - centre).Length() < _radius;
}

bool CircleCollider::IsCollision(shared_ptr<CircleCollider> other)
{
	return (other->centre - centre).Length() < (_radius + other->_radius);
}

bool CircleCollider::IsCollision(shared_ptr<RectCollider> other)
{
	return other->IsCollision(shared_from_this());
}