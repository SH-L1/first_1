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
	shared_ptr<Player> _player;
	shared_ptr<Bow> _bow;
	shared_ptr<Quad> _monster;
	vector<shared_ptr<Bullet>> _bullets;

	shared_ptr<Transform> _muzzle;

	shared_ptr<RectCollider> _rectCollider;
};