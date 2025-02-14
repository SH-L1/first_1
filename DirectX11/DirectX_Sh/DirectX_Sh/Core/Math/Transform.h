#pragma once

class MatrixBuffer;

class Transform
{
public:
	Transform();
	~Transform();

	void Update();
	void SetVS(int slot);

	void SetPos(Vector pos) { _pos = pos; }
	void SetScale(Vector scale) { _scale = scale; }
	void SetAngle(float angle) { _angle = angle; }

	Vector GetLocalPos() { return _pos; }
	Vector GetWorldPos();
	Vector GetScale() { return _scale; }
	Vector GetWorldScale();
	float GetAngle() { return _angle; }

	void AddPos(Vector pos) { _pos += pos; }
	void AddScale(Vector scale) { _scale += scale; }
	void AddAngle(float angle) { _angle += angle; }

	void SetParent(shared_ptr<Transform> parent) { _parent = parent; }
	XMMATRIX GetMatrix() { return _srtMatrix; }

private:
	Vector _pos = { 0.0f, 0.0f };
	Vector _scale = { 1.0f, 1.0f };
	float _angle = 0.0f;
	XMMATRIX _srtMatrix;

	shared_ptr<MatrixBuffer> _world;

	weak_ptr<Transform> _parent;
};