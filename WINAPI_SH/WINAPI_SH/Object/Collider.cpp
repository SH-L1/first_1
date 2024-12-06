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
	return false;
}
