#pragma once

class DunPlayer
{
public:
	DunPlayer();
	~DunPlayer();

	void PreUpdate();
	void Update();
	void Render();
	void PostRender();

	bool IsDead() { return _isDead; }
	void SetAim();
	
	shared_ptr<Transform> GetTransform() { return _player->GetTransform(); }
	shared_ptr<RectCollider> GetCollider() { return _collider; }
	shared_ptr<Transform> GetMuzzle() { return _muzzle; }
	Vector GetAim() { return _bowDir; }

	void TakeDamage(int damage);
	void Move();

	void CreateBow();

	void CreateBible();
	void ActivateBible();
	void UpdateBible();

private:
	shared_ptr<Quad> _player;
	shared_ptr<RectCollider> _collider;
	shared_ptr<class DunBow> _bow;
	vector<shared_ptr<class Bible>> _bibles;
	
	shared_ptr<Transform> _muzzle;
	shared_ptr<Transform> _playerBow;
	shared_ptr<Transform> _playerBible;

private:
	int _hp = 10;
	float _playerSpeed = 300.0f;
	bool _isDead = false;

	float _bibleTime = 0.0f;
	int _bibleNum = 3;
	int _bibleCount = 0;
	float _bibleRadius = 700.0f;

	Vector _bowDir = Vector(1, 0);
};