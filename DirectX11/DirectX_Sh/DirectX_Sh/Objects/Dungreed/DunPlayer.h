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

	void SetAim();
	
	bool GetActive() { return _isActive; }
	shared_ptr<Transform> GetTransform() { return _player->GetTransform(); }
	shared_ptr<RectCollider> GetCollider() { return _collider; }
	int GetDamage() { return _damage; }

	void TakeDamage(int damage);
	void Move();
	void Fire();

	void CreateBow();
	void CreateBullet();

	void CreateBible();
	void ActivateBible();
	void UpdateBible();

	bool IsCollision_Bullet(shared_ptr<Collider> other);
	bool IsCollision_Bible(shared_ptr<Collider> other);

private:
	shared_ptr<Quad> _player;
	shared_ptr<RectCollider> _collider;
	shared_ptr<class DunBow> _bow;

	vector<shared_ptr<class DunBullet>> _bullets;
	vector<shared_ptr<class Bible>> _bibles;
	
	shared_ptr<Transform> _muzzle;
	shared_ptr<Transform> _playerBow;
	shared_ptr<Transform> _playerBible;

private:
	int _hp = 10;
	int _damage = 1;
	float _playerSpeed = 300.0f;
	bool _isActive = true;

	float _bibleTime = 0.0f;
	int _bibleNum = 3;
	int _bibleCount = 0;
	float _bibleRadius = 1000.0f;

	int _bulletNum = 30;
	int _curMag = 0;

	Vector _bowDir = Vector(1, 0);
};