#pragma once

class IndexBuffer
{
public:
	IndexBuffer(void* data, UINT count);
	~IndexBuffer();

	void IASetIndexBuffer();

private:
	void CreateIndexBuffer(void* data);

	Microsoft::WRL::ComPtr<ID3D11Buffer> _indexBuffer;

	UINT _count;
};