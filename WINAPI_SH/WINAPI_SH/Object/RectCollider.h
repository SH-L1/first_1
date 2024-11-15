#pragma once

class RectCollider
{
public:
	RectCollider(Vector2D centre, Vector2D size);
	
	void Render(HDC hdc);

private:
	Vector2D _centre;
	Vector2D _size;
};