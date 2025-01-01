#pragma once

class Energy
{
public:
	Energy(float radius);
	~Energy();

	void Update();
	void Render(HDC hdc);

	void SetPos(Vector2D startpos) { _energy->centre = startpos; }
	void SetDir(Vector2D dir) { dir.Normalize(); _dir = dir; }
	void SetVelocity(float speed) { _velocity = _dir * speed; }

	bool EnergyDrop();

	shared_ptr<Collider> GetCollider() { return _energy; }

private:
	shared_ptr<CircleCollider> _energy;

	Vector2D _dir = Vector2D(0, 1);
	Vector2D _velocity = Vector2D(0, 0);
};