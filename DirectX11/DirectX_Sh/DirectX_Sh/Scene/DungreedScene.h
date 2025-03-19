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

	void CollisionCheck();

private:	
	void PlayerCollision();
	void MonsterCollision();
	void SkeletonCollision();

	void ActivateSkeleton();

private:
	shared_ptr<class Background> _background;

	shared_ptr<class DunPlayer> _player;
	shared_ptr<class DunMonster> _monster;
	vector<shared_ptr<class DunSkeleton>> _skeletons;

private:
	int _skeletonNum = 30;

	float _damageTime = 0.0f;
	float _skeletonSpawnTime = 0.0f;
	float _bibleDamageTime = 0.0f;
};