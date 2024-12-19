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
	auto rect = dynamic_pointer_cast<RectCollider>(other);
	if (rect != nullptr) return IsCollision(rect);

	auto circle = dynamic_pointer_cast<CircleCollider>(other);
	if (circle != nullptr) return IsCollision(circle);

	return false;
}
