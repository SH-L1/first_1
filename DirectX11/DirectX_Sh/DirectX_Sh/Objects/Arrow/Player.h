#pragma once

class Player : public Quad
{
public:
	Player(wstring textureFile);
	~Player();

	void Update() override;
	void Render() override;

	void CreateMesh() override;

	void Move();

private:
	int _hp = 10;
	int _atk = 1;

	float _playerSpeed = 300.0f;
};