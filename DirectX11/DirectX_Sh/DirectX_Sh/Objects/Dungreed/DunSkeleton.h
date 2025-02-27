#pragma once

class DunSkeleton
{
public:
	DunSkeleton();
	~DunSkeleton();

	void PreUpdate();
	void Update();
	void Render();
	void PostRender();

	void SetActive(bool active) { _isActive = active; }

	bool GetActive() { return _isActive; }
	shared_ptr<Transform> GetTransform() { return _skeleton->GetTransform(); }
	shared_ptr<RectCollider> GetCollider() { return _collider; }
	int GetDamage() { return _atk; }

	void TakeDamage(int damage);

	void Move(shared_ptr<Collider> other);

	bool IsCollision_Skeleton(shared_ptr<Collider> other);

private:
	shared_ptr<Quad> _skeleton;
	shared_ptr<RectCollider> _collider;

private:
	int _hp = 3;
	int _atk = 1;

	float _speed = 30.0f;

	bool _isActive = false;
};