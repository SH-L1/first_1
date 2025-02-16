#include "framework.h"
#include "DunBow.h"

DunBow::DunBow(wstring textureFile)
	: Quad(textureFile)
{
	Init();
}

DunBow::~DunBow()
{
}

void DunBow::PreUpdate()
{
}

void DunBow::Update()
{
	Quad::Update();
}

void DunBow::Render()
{
	Quad::Render();
}

void DunBow::PostRender()
{
}

void DunBow::CreateMesh()
{
    Vector _halfSize = _srv->GetImageSize() * 0.5f;

    _vertices =
    {
        { XMFLOAT3(-_halfSize.x, _halfSize.y, 0.0f), XMFLOAT2(0, 0) },
        { XMFLOAT3(_halfSize.x, _halfSize.y, 0.0f), XMFLOAT2(1, 0) },
        { XMFLOAT3(_halfSize.x, -_halfSize.y, 0.0f), XMFLOAT2(1, 1) },
        { XMFLOAT3(-_halfSize.x, -_halfSize.y, 0.0f), XMFLOAT2(0, 1) }
    };

    _indices.push_back(0);
    _indices.push_back(1);
    _indices.push_back(2);

    _indices.push_back(0);
    _indices.push_back(2);
    _indices.push_back(3);

    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex_Texture), _vertices.size(), 0);
    _indexBuffer = make_shared<IndexBuffer>(&_indices[0], _indices.size());
}