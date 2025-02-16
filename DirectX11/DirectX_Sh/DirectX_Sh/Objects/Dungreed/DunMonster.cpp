#include "framework.h"
#include "DunMonster.h"

DunMonster::DunMonster(wstring textureFile)
	: Quad(textureFile)
{
	Init();

	_collider = make_shared<RectCollider>(GetImageSize());
	_collider->SetParent(GetTransform());
    _collider->GetTransform()->SetPos(GetTransform()->GetWorldPos());
}

DunMonster::~DunMonster()
{
}

void DunMonster::PreUpdate()
{
    if (_isActive == false) return;
    if (_isDead == true) return;

	_collider->Update();
}

void DunMonster::Update()
{
    if (_isActive == false) return;
    if (_isDead == true) return;

	Quad::Update();
}

void DunMonster::Render()
{
    if (_isActive == false) return;
    if (_isDead == true) return;

	Quad::Render();
}

void DunMonster::PostRender()
{
    if (_isActive == false) return;
    if (_isDead == true) return;

	_collider->Render();
}

void DunMonster::CreateMesh()
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

void DunMonster::TakeDamage(int damage)
{
    _hp -= damage;

    if (_hp == 0)
        _isDead = true;
}

void DunMonster::Move(shared_ptr<Quad> _player)
{
    Vector _playerPos = _player->GetTransform()->GetWorldPos();
    Vector _monsterPos = GetTransform()->GetWorldPos();

    Vector _dir = (_playerPos - _monsterPos).NormalVector();

    if (abs(_playerPos.x - _monsterPos.x) <= 0.1f && abs(_playerPos.y - _monsterPos.y) <= 0.1f) return;

    GetTransform()->AddPos(_dir * _speed * DELTA_TIME);

    // TODO : Ãæµ¹ ½Ã, »ìÂ¦ ¿·À¸·Î Æ¨°ÜÁ® ³ª°¨
}