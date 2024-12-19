#pragma once

class Line
{
public:
	struct HitResult
	{
		bool isCollision = false;
		
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

	HitResult IsCollision(shared_ptr<Line> other);

public:
	Color _curColor = Color::C_GREEN;
	vector<HPEN> _pens;
};
