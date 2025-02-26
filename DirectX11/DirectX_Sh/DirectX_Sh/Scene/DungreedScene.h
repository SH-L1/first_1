#pragma once

class DungreedScene : public Scene
{
public:
	DungreedScene();
	~DungreedScene();

	virtual void PreUpdate() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void Input();
	void CollisionManager();

private:
	void Fire(shared_ptr<class DunBullet> bullet);
	
	void PlayerCollision();
	void MonsterCollision();

private:
	shared_ptr<class Background> _background;

	shared_ptr<class DunPlayer> _player;
	shared_ptr<class DunBow> _bow;
	shared_ptr<class DunMonster> _monster;
	vector<shared_ptr<class DunBullet>> _bullets;

private:
	int _bulletNum = 30;
	int _curMag = 0;
	int _fullMag = 5;
	
	float _damageTime = 0.0f;
};