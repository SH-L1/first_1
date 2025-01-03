#pragma once

class Slow
{
public:
	Slow();
	~Slow();

	void Update();
	void Render(HDC hdc);

	void StartPos(Vector2D startpos) { _slow->centre = startpos; }
	void SetDir(Vector2D dir) { dir.Normalize(); _dir = dir; }
	void SetVelocity(float speed) { _velocity = _dir * speed; }

	float MakeEnergySlow();
	bool MissItem();

	bool IsCollision_Bar(shared_ptr<RectCollider> bar);

	shared_ptr<Collider> GetCollider() { return _slow; }

private:
	shared_ptr<CircleCollider> _slow;

	Vector2D _dir = Vector2D(0, 1);
	Vector2D _velocity = Vector2D(0, 0);

private:
	float durationTime = 5.0f;
	float time = 0.0f;
	float _radius = 8.0f;
};