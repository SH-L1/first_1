#pragma once

class Monster : public Quad
{
public:
	Monster(wstring textureFile);
	~Monster();

	void Update() override;
	void Render() override;

	void CreateMesh() override;

	void Move(shared_ptr<Quad> _player);

private:
	int _hp = 3;
	int _atk = 1;

	float _speed = 50.0f;

	bool _isActive = false;
};