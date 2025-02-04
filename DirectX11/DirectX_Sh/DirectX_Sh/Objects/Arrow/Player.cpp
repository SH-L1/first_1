#include "framework.h"
#include "Player.h"

Player::Player(wstring textureFile)
	: Quad(textureFile)
{
}

Player::~Player()
{
}

void Player::Update()
{
    Quad::Update();
}

void Player::Render()
{
    Quad::Render();
}

void Player::CreateMesh()
{
    _vertices =
    {
        { XMFLOAT3(-254, 326, 0.0f), XMFLOAT2(0, 0) },
        { XMFLOAT3(254, 326, 0.0f), XMFLOAT2(1, 0) },
        { XMFLOAT3(254, -326, 0.0f), XMFLOAT2(1, 1) },
        { XMFLOAT3(-254, -326, 0.0f), XMFLOAT2(0, 1) }
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