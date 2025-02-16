#pragma once

class DungreedScene : public Scene
{
public:
	DungreedScene();
	~DungreedScene();

	void PreUpdate() override;
	void Update() override;
	void Render() override;
	void PostRender() override;

	void Input();
	void CollisionManage();

private:
	void Fire(shared_ptr<class DunBullet> _bullet);
	void Reload();
	void AutoReload();

	void PlayerCollision();
	void MonsterCollision();

private:
	shared_ptr<class DunPlayer> _player;
	shared_ptr<class DunBow> _bow;
	shared_ptr<class DunMonster> _monster;
	vector<shared_ptr<class DunBullet>> _bullets;

	shared_ptr<Transform> _muzzle;

private:
	int _bulletNum = 30;
	int _curMag = 0;
	int _fullMag = 5;
	
	float _time = 0.0f;
	float _autoTime = 3.0f;
};