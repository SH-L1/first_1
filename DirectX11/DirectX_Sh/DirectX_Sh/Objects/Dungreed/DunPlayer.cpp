#include "framework.h"
#include "DunPlayer.h"

DunPlayer::DunPlayer(wstring textureFile)
	: Quad(textureFile)
{
	Init();

	_collider = make_shared<RectCollider>(GetImageSize());
	_collider->SetParent(GetTransform());
	_collider->GetTransform()->SetScale(Vector(0.9f, 0.9f));
	_collider->GetTransform()->SetPos(GetTransform()->GetWorldPos());
}

DunPlayer::~DunPlayer()
{
}

void DunPlayer::PreUpdate()
{
	if (_isDead == true)
		return;

	_collider->Update();
}

void DunPlayer::Update()
{
	if (_isDead == true)
		return;

	Move();

	Quad::Update();
}

void DunPlayer::Render()
{
	if (_isDead == true)
		return;

	Quad::Render();
}

void DunPlayer::PostRender()
{
	if (_isDead == true)
		return;

	_collider->Render();
}

void DunPlayer::CreateMesh()
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

void DunPlayer::Move()
{
	Vector moveDir = Vector(0, 0);

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

void DunPlayer::TakeDamage(int damage)
{
	_hp -= damage;

	if (_hp == 0)
		_isDead = true;
}

// TODO : 몬스터와 충돌 시, 잠시 동안 무적