#pragma once

class RectCollider : public Collider
{
public:
	RectCollider(Vector2D centre, Vector2D size);
	~RectCollider();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;

	int Left() { return _centre.x - _halfSize.x; }
	int Right() { return _centre.x + _halfSize.x; }
	int Top() { return _centre.y - _halfSize.y; }
	int Bottom() { return _centre.y + _halfSize.y; }

private:
	Vector2D _halfSize;
};