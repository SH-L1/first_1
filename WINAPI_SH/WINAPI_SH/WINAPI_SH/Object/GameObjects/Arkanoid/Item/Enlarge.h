#pragma once

class Enlarge
{
public:
	Enlarge();
	~Enlarge();

	void Update();
	void Render(HDC hdc);

	void StartPos(Vector2D startpos) { _enlarge->centre = startpos; }
	void SetDir(Vector2D dir) { dir.Normalize(); _dir = dir; }
	void SetVelocity(float speed) { _velocity = _dir * speed; }

	bool MissItem();

	bool IsCollision_Bar(shared_ptr<RectCollider> bar);

	shared_ptr<Collider> GetCollider() { return _enlarge; }

private:
	shared_ptr<CircleCollider> _enlarge;

	Vector2D _dir = Vector2D(0, 1);
	Vector2D _velocity = Vector2D(0, 0);

private:
	float _radius = 8.0f;
};