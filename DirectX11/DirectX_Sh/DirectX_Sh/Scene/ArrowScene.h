#pragma once

class ArrowScene : public Scene
{
public:
	ArrowScene();
	~ArrowScene();

	void Update() override;
	void Render() override;

private:
	shared_ptr<Player> _player;
	shared_ptr<Bow> _bow;
	shared_ptr<Quad> _bullet;
	shared_ptr<Quad> _monster;

	shared_ptr<Transform> _arrowTrans;
};