#pragma once

class Quad
{
public:
	Quad(wstring textureFile);
	~Quad();

	virtual void PreUpdate() {};
	virtual void Update();
	virtual void Render();
	virtual void PostRender() {};

	void Init();
	void CreateMaterial(wstring textureFile);
	virtual void CreateMesh();

	Vector GetImageSize() { return _srv->GetImageSize(); }
	shared_ptr<Transform> GetTransform() { return _transform; }

protected:
	vector<Vertex_Texture> _vertices;
	vector<UINT> _indices;

	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;

	shared_ptr<VertexShader> _vs;
	shared_ptr<PixelShader> _ps;

	shared_ptr<SRV> _srv;

	shared_ptr<Transform> _transform;
};