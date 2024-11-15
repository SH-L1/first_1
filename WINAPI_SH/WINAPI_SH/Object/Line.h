#pragma once

class Line
{
public:
	Line(Vector2D start, Vector2D end);
	
	void Render(HDC hdc);

private:
	LPPOINT lpPoint;
	Vector2D _start;
	Vector2D _end;
};

