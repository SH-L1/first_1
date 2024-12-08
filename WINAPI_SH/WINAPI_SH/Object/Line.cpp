#include "framework.h"
#include "Line.h"

Line::Line(Vector2D start, Vector2D end)
	: lpPoint(nullptr), _start(start), _end(end)
{
}

Line::~Line()
{
}

void Line::Update()
{
}

void Line::Render(HDC hdc)
{
	MoveToEx(hdc, _start.x, _start.y, lpPoint);
	LineTo(hdc, _end.x, _end.y);
}
