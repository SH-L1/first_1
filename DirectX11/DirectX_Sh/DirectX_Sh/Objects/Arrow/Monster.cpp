#include "framework.h"
#include "Monster.h"

Monster::Monster(wstring textureFile)
	: Quad(textureFile)
{
    Init();
}

Monster::~Monster()
{
}

void Monster::Update()
{
	Quad::Update();
}

void Monster::Render()
{
	Quad::Render();
}

void Monster::CreateMesh()
{
    _vertices =
    {
		{ XMFLOAT3(-270, 290, 0.0f), XMFLOAT2(0, 0) },
		{ XMFLOAT3(270, 290, 0.0f), XMFLOAT2(1, 0) },
		{ XMFLOAT3(270, -290, 0.0f), XMFLOAT2(1, 1) },
		{ XMFLOAT3(-270, -290, 0.0f), XMFLOAT2(0, 1) }
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

void Monster::Move()
{
    
}