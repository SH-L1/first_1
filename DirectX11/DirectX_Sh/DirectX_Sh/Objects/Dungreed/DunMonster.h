#pragma once

class DunMonster : public Quad
{
public:
	DunMonster(wstring textureFile);
	~DunMonster();

	void PreUpdate() override;
	void Update() override;
	void Render() override;
	void PostRender() override;

	void CreateMesh() override;

	void SetActive(bool active) { _isActive = active; }
	
	bool GetActive() { return _isActive; }
	bool IsDead() { return _isDead; }
	shared_ptr<RectCollider> GetCollider() { return _collider; }
	int GetDamage() { return _atk; }

	void TakeDamage(int damage);

	void Move(shared_ptr<Quad> _player);

private:
	shared_ptr<RectCollider> _collider;

private:
	int _hp = 10;
	int _atk = 1;

	float _speed = 50.0f;

	bool _isActive = false;
	bool _isDead = false;
};