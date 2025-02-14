#include "framework.h"
#include "Bullet.h"

Bullet::Bullet(wstring textureFile)
	: Quad(textureFile)
{
    Init();
    _collider = make_shared<RectCollider>(GetTransform()->GetScale());
    _collider->SetParent(GetTransform());
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
    if (_isActive == false) return;

	Quad::Update();
    _collider->Update();

    GetTransform()->AddPos(_bulletDir * _bulletSpeed * TimeManager::Instance()->DeltaTime());

    _time += TimeManager::Instance()->DeltaTime();

    if (_time > _lifeTime)
    {
        _time = 0.0f;
        _isActive = false;
    }
}

void Bullet::Render()
{
    if (_isActive == false) return;

	Quad::Render();
    _collider->Render();
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

void Bullet::SetDir(Vector dir)
{
    _bulletDir = dir.NormalVector();
}

void Bullet::SetPos(Vector pos)
{
    GetTransform()->SetPos(pos);
}

void Bullet::SetAngle(float angle)
{
    GetTransform()->SetAngle(angle);
}