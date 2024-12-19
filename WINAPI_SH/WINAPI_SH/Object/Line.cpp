#include "framework.h"
#include "Line.h"

Line::Line()
{
	_pens.push_back(CreatePen(3, 3, GREEN));
	_pens.push_back(CreatePen(3, 3, RED));
}

Line::~Line()
{
	for (auto& pen : _pens)
	{
		DeleteObject(pen);
	}
}

Line::HitResult Line::IsCollision(shared_ptr<Line> other)
{
	return HitResult();
}
