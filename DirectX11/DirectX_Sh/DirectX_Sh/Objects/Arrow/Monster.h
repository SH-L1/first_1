#pragma once

class Monster : public Quad
{
public:
	Monster(wstring textureFile);
	~Monster();

	void Update() override;
	void Render() override;

	void CreateMesh() override;

private:
	vector<Vertex_Texture> _vertices;
};