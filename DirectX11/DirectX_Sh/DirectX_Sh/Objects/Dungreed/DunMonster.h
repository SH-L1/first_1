#pragma once

class DunMonster
{
public:
	DunMonster();
	~DunMonster();

	void PreUpdate();
	void Update();
	void Render();
	void PostRender();

	void SetActive(bool active) { _isActive = active; }
	
	bool GetActive() { return _isActive; }
	shared_ptr<Transform> GetTransform() { return _monster->GetTransform(); }
	shared_ptr<RectCollider> GetCollider() { return _collider; }
	int GetDamage() { return _atk; }

	void TakeDamage(int damage);

	void Move(shared_ptr<Collider> other);

	bool IsCollision_Monster(shared_ptr<Collider> other);

private:
	shared_ptr<Quad> _monster;
	shared_ptr<RectCollider> _collider;

private:
	int _hp = 10;
	int _atk = 1;

	float _speed = 50.0f;

	bool _isActive = false;
};