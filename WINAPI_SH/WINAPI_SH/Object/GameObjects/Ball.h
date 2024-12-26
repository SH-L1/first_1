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
	void SetShot() { _shot = true; }
	void SetVelocity(float initialSpeed) { _velocity = _dir * initialSpeed; }

	void SetActive(bool value) { _isActive = value; }
	bool IsActive() { return _isActive; }

	void HitTarget();

	bool BallEnd(float floor);

private:
	shared_ptr<CircleCollider> _circle;

	float _radius;
	bool _shot = false;
	bool _isActive = false;

private:
	const float _gravity = 0.08f;
	Vector2D _velocity = Vector2D(0, 0);

private:
	Vector2D _dir = Vector2D(1, 0);
};