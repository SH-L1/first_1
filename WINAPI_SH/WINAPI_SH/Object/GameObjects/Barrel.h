#pragma once

class Barrel
{
public:
	Barrel(float length);
	~Barrel();

	void Update();
	void Render(HDC hdc);

	void UpdateBody(Vector2D bodycentre) { _line->_start = bodycentre; }
	void SetDir(Vector2D dir) { _dir = dir; }

	Vector2D GetEndPoint() { return _line->_end; }

private:
	shared_ptr<LineCollider> _line;
	float _length = 100.0;

	Vector2D _dir = Vector2D(1, 0);
};

