#pragma once

class Line
{
public:
	struct HitResult
	{
		bool isCollision = false;
		Vector2D point;
	};

	enum Color
	{
		C_GREEN = 0,
		C_RED = 1
	};

	Line();
	virtual ~Line();
	
	virtual void Update() = 0;
	virtual void Render(HDC hdc) = 0;

	void SetRed() { _curColor = Color::C_RED; }
	void SetGreen() { _curColor = Color::C_GREEN; }

	virtual HitResult IsCollision(shared_ptr<Line> other);

public:
	Vector2D _start;
	Vector2D _end;

	Color _curColor = C_GREEN;
	vector<HPEN> _pens;
};
