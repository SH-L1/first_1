#include "framework.h"
#include "VertexBuffer.h"

VertexBuffer::VertexBuffer()
{
    stride = sizeof(Vertex_Texture);
    offset = 0;

    CreateVertices();
    CreateVertexBuffer();
}

VertexBuffer::~VertexBuffer()
{
}

void VertexBuffer::IASet(int slot)
{
    DC->IASetVertexBuffers(slot, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
}

void VertexBuffer::CreateVertices()
{
    _vertices =
    {
        { XMFLOAT3(-0.5f, 0.5f, 0.0f), XMFLOAT2(0,0) }, //  좌측 상단
        { XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT2(2,2) }, // 우측 하단
        { XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT2(0,2)}, // 좌측 하단

        { XMFLOAT3(-0.5f, 0.5f, 0.0f), XMFLOAT2(0,0)}, // 좌측 상단
        { XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT2(2,0)}, // 우측 상단
        { XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT2(2,2)} // 우측 하단
    };
}

void VertexBuffer::CreateVertexBuffer()
{
  
    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = stride * 6;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = &_vertices[0];

    DEVICE->CreateBuffer(&bd, &initData, vertexBuffer.GetAddressOf());
}
