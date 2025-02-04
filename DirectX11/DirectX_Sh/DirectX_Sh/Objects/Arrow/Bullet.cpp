#include "framework.h"
#include "Bullet.h"

Bullet::Bullet(wstring textureFile)
	: Quad(textureFile)
{
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	Quad::Update();
}

void Bullet::Render()
{
	Quad::Render();
}

void Bullet::CreateMesh()
{
    _vertices =
    {
        { XMFLOAT3(-100, 100, 0.0f), XMFLOAT2(0, 0) },
        { XMFLOAT3(100, 100, 0.0f), XMFLOAT2(1, 0) },
        { XMFLOAT3(100, -100, 0.0f), XMFLOAT2(1, 1) },
        { XMFLOAT3(-100, -100, 0.0f), XMFLOAT2(0, 1) }
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