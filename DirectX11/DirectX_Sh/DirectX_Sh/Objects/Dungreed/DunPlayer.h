#pragma once

class DunPlayer : public Quad
{
public:
	DunPlayer(wstring textureFile);
	~DunPlayer();

	void PreUpdate() override;
	void Update() override;
	void Render() override;
	void PostRender() override;

	void CreateMesh() override;

	shared_ptr<RectCollider> GetCollider() { return _collider; }
	bool IsDead() { return _isDead; }

	void Move();
	void TakeDamage(int damage);

private:
	shared_ptr<RectCollider> _collider;

private:
	int _hp = 10;
	float _playerSpeed = 300.0f;

	bool _isDead = false;
};