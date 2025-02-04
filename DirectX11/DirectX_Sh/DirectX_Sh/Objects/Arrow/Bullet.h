#pragma once

class Bullet : public Quad
{
public:
	Bullet(wstring textureFile);
	~Bullet();

	void Update() override;
	void Render() override;

	void CreateMesh() override;

private:
	vector<Vertex_Texture> _vertices;
};