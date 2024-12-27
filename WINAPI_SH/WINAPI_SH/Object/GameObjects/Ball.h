#pragma once

class Ball
{
public:
	Ball(float radius);
	~Ball();

	void Update();
	void Render(HDC hdc);

	void UpdateBody(Vector2D barrelend) { _circle->centre = barrelend; }
	void SetDir(Vector2D dir) { dir.Normalize(); _dir = dir; }
	void SetVelocity(float initialSpeed) { _velocity = _dir * initialSpeed; }

	void SetActive(bool value) { _isActive = value; }
	bool IsActive() { return _isActive; }
	bool BallEnd(float floor);

	shared_ptr<Collider> GetCollider() { return _circle; }

private:
	shared_ptr<CircleCollider> _circle;

	float _radius;
	bool _isActive = false;

private:
	const float _gravity = 0.08f;
	Vector2D _velocity = Vector2D(0, 0);
	Vector2D _dir = Vector2D(1, 0);
};