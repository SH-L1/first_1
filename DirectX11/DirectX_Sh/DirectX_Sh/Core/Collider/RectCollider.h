#pragma once

class RectCollider : public Collider
{
public:
	RectCollider(Vector centre, Vector size);
	~RectCollider();

	virtual void Update() override;
	virtual void Render() override;

	shared_ptr<Transform> GetTransform() { return _transform; }

	int Left() { return centre.x - _halfSize.x; }
	int Right() { return centre.x + _halfSize.x; }
	int Top() { return centre.y - _halfSize.y; }
	int Bottom() { return centre.y + _halfSize.y; }

	virtual bool IsCollision(const Vector& pos) override;
	virtual bool IsCollision(shared_ptr<class RectCollider> other) override;
	virtual bool IsCollision(shared_ptr<class CircleCollider> other) override;

	Vector GetClosestPoint(const Vector& point);

private:
	Vector _halfSize;
	Vector _centre;

private:
	void CreateMesh();
	void CreateMaterial();

private:
	vector<Vertex> _vertices;
	shared_ptr<VertexBuffer> _vertexBuffer;

	shared_ptr<VertexShader> _vs;	
	shared_ptr<PixelShader> _ps;

	shared_ptr<Transform> _transform;
	shared_ptr<ColorBuffer> _colorBuffer;
};