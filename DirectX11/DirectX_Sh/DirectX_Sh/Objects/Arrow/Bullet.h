#pragma once

class Bullet : public Quad
{
public:
	Bullet(wstring textureFile);
	~Bullet();

	void Update() override;
	void Render() override;

	void CreateMesh() override;

	void SetDir(Vector dir);
	void SetPos(Vector pos);
	void SetAngle(float angle);
	void SetActive(bool active) { _isActive = active; }
	
	bool GetActive() { return _isActive; }

private:
	vector<Vertex_Texture> _vertices;

private:
	float _lifeTime = 5.0f;
	float _time = 0.0f;

	bool _isActive = false;
	Vector _bulletDir = Vector(0, 0);
	float _bulletSpeed = 700.0f;
};