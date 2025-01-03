#pragma once

class Catch
{
public:
	Catch();
	~Catch();

	void Update();
	void Render(HDC hdc);

	void StartPos(Vector2D startpos) { _catch->centre = startpos; }
	void SetDir(Vector2D dir) { dir.Normalize(); _dir = dir; }
	void SetVelocity(float speed) { _velocity = _dir * speed; }

	bool MissItem();

	bool IsCollision_Bar(shared_ptr<RectCollider> bar);

	shared_ptr<Collider> GetCollider() { return _catch; }

private:
	shared_ptr<CircleCollider> _catch;

	Vector2D _dir = Vector2D(0, 1);
	Vector2D _velocity = Vector2D(0, 0);

private:
	float _radius = 8.0f;
};