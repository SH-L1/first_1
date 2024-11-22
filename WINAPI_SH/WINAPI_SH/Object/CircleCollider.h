#pragma once

class CircleCollider
{
public:
	CircleCollider(Vector2D centre, float radius);

	void Update();
	void Render(HDC hdc);

private:
	Vector2D _centre;
	float _radius;
};