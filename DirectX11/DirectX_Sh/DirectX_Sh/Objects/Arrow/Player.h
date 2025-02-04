#pragma once

class Player : public Quad
{
public:
	Player(wstring textureFile);
	~Player();

	void Update() override;
	void Render() override;

	void CreateMesh() override;

private:
	vector<Vertex_Texture> _vertices;
};