#include "framework.h"
#include "LineCollider.h"

LineCollider::LineCollider(Vector2D start, Vector2D end)
	: _start(start), _end(end)
{
}

void LineCollider::Update()
{
}

void LineCollider::Render(HDC hdc)
{
	SelectObject(hdc, Line::_pens[_curColor]);
	MoveToEx(hdc, _start.x, _start.y, lpPoint);
	LineTo(hdc, _end.x, _end.y);
}

bool LineCollider::IsCollision(shared_ptr<LineCollider> other)
{
	// 삼각형 넓이 a, b
	float a = 0;
	float b = 0;

	// Line1 기준에서 Line2의 양쪽 끝으로 향하는 벡터 사이에 있는지
	bool isBetween1 = false;
	{
		Vector2D line1V = _end - _start;
		Vector2D line1_2Start = other->_start - _start;
		Vector2D line1_2End = other->_end - _start;

		float cross1 = line1V.Cross(line1_2Start);
		a = abs(cross1);
		float cross2 = line1V.Cross(line1_2End);
		b = abs(cross2);
		// 만약 사이에 없다면. => 부호가 같음
		// 사이에 있으면 부호가 다르기 때문에 
		isBetween1 = (cross1 * cross2) < 0;
	}
	
	// Line2 기준에서 Line1의 양쪽 끝으로 향하는 벡터 사이에 있는지
	bool isBetween2 = false;
	{
		Vector2D line2V = other->_end - other->_start;
		Vector2D line2_1Start = _start - other->_start;
		Vector2D line2_1End = _end - other->_start;

		float cross1 = line2V.Cross(line2_1Start);
		float cross2 = line2V.Cross(line2_1End);

		isBetween2 = (cross1 * cross2) < 0;
	}

	Vector2D dir = (other->_end - other->_start).NormalVector();
	float ratio = a / (a + b);
	Vector2D crashPoint = LERP(other->_start, other->_end, ratio);

	return isBetween1 && isBetween2;
}

// 왜 Length() 까지?