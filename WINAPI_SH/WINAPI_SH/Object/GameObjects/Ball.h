#pragma once

class Ball
{
public:
	Ball(float radius);
	~Ball();

	void Update();
	void Render(HDC hdc);

	void UpdateBody(Vector2D barrelend) { _circle->centre = barrelend; }
	void SetDir(Vector2D dir) { _dir = dir; }
	Vector2D ResetLC() { return _reset; }

	bool BallEnd();

private:
	shared_ptr<CircleCollider> _circle;
	
	float _radius;
	float _speed = 100.0f;

	Vector2D _dir = Vector2D(1, 0);
	Vector2D _reset = Vector2D(-_radius, -_radius);
};