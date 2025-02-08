#pragma once

class Monster : public Quad
{
public:
	Monster(wstring textureFile);
	~Monster();

	void Update() override;
	void Render() override;

	void CreateMesh() override;

	void Move();

private:
	vector<Vertex_Texture> _vertices;

private:
	int _hp = 3;
	int _atk = 1;

	bool _isActive = false;
};