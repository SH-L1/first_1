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

private:
	shared_ptr<class Background> _background;

	shared_ptr<class DunPlayer> _player;
	shared_ptr<class DunMonster> _monster;

private:
	float _damageTime = 0.0f;
};