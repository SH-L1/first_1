#pragma once

class Item
{
public:
	enum class Type {
		Enlarge,
		Slow
	};

	Item(Type type);
	~Item();

	void Update();
	void Render(HDC hdc);

	void StartPos();
	void SetDir(Vector2D dir) { dir.Normalize(); _dir = dir; }
	void SetVelocity(float speed) { _velocity = _dir * speed; }

	void SetActive(bool value) { _isActive = value; }
	bool IsActive() { return _isActive; }

	bool MissItem();
	float ItemUtil();

	bool IsCollision_Bar(shared_ptr<RectCollider> bar);

	shared_ptr<Collider> GetCollider() { return _item; }

private:
	shared_ptr<CircleCollider> _item;

	Vector2D _dir = Vector2D(0, 0);
	Vector2D _velocity = Vector2D(0, 0);

	Type _type;
	
	bool _isActive = false;
	float _radius = 8.0f;

	float _durationTime = 0.0f;
	float time = 0.0f;
};