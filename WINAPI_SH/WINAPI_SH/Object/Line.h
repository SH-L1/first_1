#pragma once

class Line
{
public:
	Line(Vector2D start, Vector2D end);
	
	void Update();
	void Render(HDC hdc);

public:
	LPPOINT lpPoint;
	Vector2D _start;
	Vector2D _end;
};

