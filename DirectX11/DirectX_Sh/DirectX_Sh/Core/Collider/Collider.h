#pragma once

class Collider
{
protected:
	enum Type
	{
		NONE,
		CIRCLE,
		RECT
	};

public:
	Collider(Type type);
	virtual ~Collider();

	virtual void Update();
	virtual void Render();

	void CreateMaterial();
	virtual void CreateMesh() = 0;

	bool IsCollision(shared_ptr<Collider> other);

	virtual bool IsCollision(const Vector& pos) = 0;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other) = 0;
	virtual bool IsCollision(shared_ptr<class RectCollider> other) = 0;

	void SetColor(XMFLOAT4 color) { _colorBuffer->SetData(color); _colorBuffer->Update(); }
	void SetRed() { _colorBuffer->SetData(RED); _colorBuffer->Update(); }
	void SetGreen() { _colorBuffer->SetData(GREEN); _colorBuffer->Update(); }

	void SetPos(Vector pos) { _transform->SetPos(pos); }
	Vector GetLocalPos() { return _transform->GetLocalPos(); }
	Vector GetWorldPos() { return _transform->GetWorldPos(); }

	const shared_ptr<Transform> GetTransform() { return _transform; }
	void SetParent(shared_ptr<Transform> transform) { _transform->SetParent(transform); }

protected:
	Type _type = NONE;

	vector<Vertex> _vertices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<Transform> _transform;
	shared_ptr<ColorBuffer> _colorBuffer;

};