#include "framework.h"
#include "RectCollider.h"

RectCollider::RectCollider(Vector2D centre, Vector2D size)
	: _halfSize(size * 0.5f)
{
	this->centre = centre;
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

bool RectCollider::IsCollision(const Vector2D& pos)
{
	if(pos.x >= Left() && pos.x <= Right() && pos.y <= Bottom() && pos.y >= Top())
		return true;

	return false;
}

bool RectCollider::IsCollision(shared_ptr<RectCollider> other)
{
	return !(Left() > other->Right() || Right() < other->Left() || Bottom() > other->Top() ||
		Top() < other->Bottom());
}

bool RectCollider::IsCollision(shared_ptr<CircleCollider> other)
{
	float closeX = max(Left(), min(other->GetCentre().x, Right()));
	float closeY = max(Top(), min(other->GetCentre().y, Bottom()));

	float distanceX = other->GetCentre().x - closeX;
	float distanceY = other->GetCentre().y - closeY;

	float result = (distanceX * distanceX) + (distanceY * distanceY);

	return result <= (other->GetRadius() * other->GetRadius());
}