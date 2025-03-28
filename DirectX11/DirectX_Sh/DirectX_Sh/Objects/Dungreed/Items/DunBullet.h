#pragma once

class DunBullet
{
public:
	DunBullet();
	~DunBullet();

	void PreUpdate();
	void Update();
	void Render();
	void PostRender();

	void SetDir(Vector dir);
	void SetPos(Vector pos);
	void SetAngle(float angle);
	void SetActive(bool active) { _isActive = active; }

	bool GetActive() { return _isActive; }
	shared_ptr<Transform> GetTransform() { return _bullet->GetTransform(); }
	shared_ptr<CircleCollider> GetCollider() { return _collider; }

private:
	shared_ptr<Quad> _bullet;
	shared_ptr<CircleCollider> _collider;

private:
	float _time = 0.0f;
	float _lifeTime = 5.0f;

	bool _isActive = false;

	Vector _bulletDir = Vector(0, 0);
	float _bulletSpeed = 500.0f;
};