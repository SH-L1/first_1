#pragma once

class ArrowScene : public Scene
{
public:
	ArrowScene();
	~ArrowScene();

	void Update() override;
	void Render() override;

	void Input();

private:
	shared_ptr<class Player> _player;
	shared_ptr<class Bow> _bow;
	shared_ptr<class Monster> _monster;
	vector<shared_ptr<class Bullet>> _bullets;

	shared_ptr<Transform> _muzzle;
};