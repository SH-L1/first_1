#pragma once

class DunBullet : public Quad
{
public:
	DunBullet(wstring textureFile);
	~DunBullet();

	void PreUpdate() override;
	void Update() override;
	void Render() override;
	void PostRender() override;

	void CreateMesh() override;

	void SetDir(Vector dir);
	void SetPos(Vector pos);
	void SetAngle(float angle);
	void SetActive(bool active) { _isActive = active; }

	bool GetActive() { return _isActive; }
	shared_ptr<CircleCollider> GetCollider() { return _collider; }
	int GetDamage() { return _damage; }

private:
	shared_ptr<CircleCollider> _collider;

private:
	int _damage = 1;

	float _time = 0.0f;
	float _lifeTime = 5.0f;

	bool _isActive = false;

	Vector _bulletDir = Vector(0, 0);
	float _bulletSpeed = 700.0f;
};