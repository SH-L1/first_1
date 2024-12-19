#include "framework.h"
#include "Collider.h"

Collider::Collider()
{
	_pens.push_back(CreatePen(3, 3, GREEN));
	_pens.push_back(CreatePen(3, 3, RED));
}

Collider::~Collider()
{
	for (auto& pen : _pens)
	{
		DeleteObject(pen);
	}
}

bool Collider::IsCollision(shared_ptr<Collider> other)
{
	switch (_type)
	{
	case Collider::NONE:
		break;
	case Collider::CIRCLE:
	{
		auto circle = dynamic_pointer_cast<CircleCollider>(other);
		return IsCollision(circle);
	}
	case Collider::RECT:
	{
		auto rect = dynamic_pointer_cast<RectCollider>(other);
		return IsCollision(rect);
	}
	default:
		break;
	}

	return false;
}
