#include "framework.h"
#include "Player.h"

Player::Player(wstring textureFile)
	: Quad(textureFile)
{
    Init();
}

Player::~Player()
{
}

void Player::Update()
{
    Move();

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

void Player::Move()
{
	Vector moveDir = Vector(0,0);
	
	if (KEY_PRESS('W'))
		moveDir.y += 1.0f;
	if (KEY_PRESS('S'))
		moveDir.y -= 1.0f;
	if (KEY_PRESS('A'))
		moveDir.x -= 1.0f;
	if (KEY_PRESS('D'))
		moveDir.x += 1.0f;
		
	if (moveDir.Length() > 0.0f)
	{
		moveDir.Normalize();
        GetTransform()->AddPos(moveDir * _playerSpeed * DELTA_TIME);
	}
}