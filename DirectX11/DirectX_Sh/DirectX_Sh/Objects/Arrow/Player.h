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
};