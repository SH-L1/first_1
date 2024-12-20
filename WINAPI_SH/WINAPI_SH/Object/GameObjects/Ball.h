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
	void SetShot() { _shot = true; }

	bool BallEnd(float floor);

	void SetVelocity(float initialSpeed) { _velocity = _dir * initialSpeed; }

private:
	shared_ptr<CircleCollider> _circle;
	
	float _radius;
	// float _speed = 10.0f;
	bool _shot = false;

private:
	float _gravity = 0.07f;
	Vector2D _velocity = Vector2D(0, 0);

private:
	Vector2D _dir = Vector2D(1, 0);
	Vector2D _reset = Vector2D(-_radius, -_radius);
};