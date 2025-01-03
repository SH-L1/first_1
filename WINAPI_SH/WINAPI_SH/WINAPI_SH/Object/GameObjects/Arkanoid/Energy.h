#pragma once

class Energy
{
public:
	Energy(float radius);
	~Energy();

	void Update();
	void Render(HDC hdc);

	void StartPos(Vector2D startpos) { _energy->centre = startpos; }
	void SetDir(Vector2D dir) { dir.Normalize(); _dir = dir; }
	void SetVelocity(float speed) { _velocity = _dir * speed; }
	Vector2D GetDir() { return _dir; }

	void SetActive(bool value) { _isActive = value; }
	bool IsActive() { return _isActive; }
	bool DeadPoint();

	bool IsCollision_Bar(shared_ptr<RectCollider> bar);
	bool IsCollision_Block(shared_ptr<RectCollider> block);

	shared_ptr<Collider> GetCollider() { return _energy; }

private:
	shared_ptr<CircleCollider> _energy;

	Vector2D _dir = Vector2D(0, 1);
	Vector2D _velocity = Vector2D(0, 0);

private:
	bool _isActive = false;
};