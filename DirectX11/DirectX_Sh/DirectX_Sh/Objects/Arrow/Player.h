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
	vector<Vertex_Texture> _vertices;

private:
	int _hp = 10;
	int _atk = 1;

	float _playerSpeed = 300.0f;
};