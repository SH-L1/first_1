#pragma once

class RectCollider
{
public:
	RectCollider(Vector2D centre, Vector2D size);
	~RectCollider();

	int Left() { return _centre.x - _halfsize.x; }
	int Right() { return _centre.x + _halfsize.x; }
	int Top() { return _centre.y - _halfsize.y; }
	int Bottom() { return _centre.y + _halfsize.y; }

	void Update();
	void Render(HDC hdc);

private:
	Vector2D _centre;
	Vector2D _halfsize;

	float _angle;
};