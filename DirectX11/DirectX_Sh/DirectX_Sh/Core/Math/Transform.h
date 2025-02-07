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
	float GetAngle() { return _angle; }

	void AddPos(Vector pos) { _pos += pos; }
	void AddAngle(float angle) { _angle += angle; }

	void SetParent(shared_ptr<Transform> parent) { _parent = parent; }
	XMMATRIX GetMatrix() { return _srtMatrix; }

private:
	Vector _pos;
	Vector _scale = { 1, 1 };
	float _angle = 0.0f;
	XMMATRIX _srtMatrix;

	shared_ptr<MatrixBuffer> _world;

	weak_ptr<Transform> _parent;
};