#include "framework.h"
#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(void* data, UINT count)
    : _count(count)
{
	CreateIndexBuffer(data);
}

IndexBuffer::~IndexBuffer()
{
}

void IndexBuffer::IASetIndexBuffer()
{
    DC->IASetIndexBuffer(_indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void IndexBuffer::CreateIndexBuffer(void* data)
{
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(int) * _count;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = data;

    DEVICE->CreateBuffer(&bd, &initData, _indexBuffer.GetAddressOf());
}