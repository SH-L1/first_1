#pragma once
class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	void IASet(int slot);

private:
	void CreateVertices();
	void CreateVertexBuffer();

	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;

	vector<Vertex_Texture> _vertices;

	UINT stride;
	UINT offset;
};

