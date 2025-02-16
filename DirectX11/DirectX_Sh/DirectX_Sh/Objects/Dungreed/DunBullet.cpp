#include "framework.h"
#include "DunBullet.h"

DunBullet::DunBullet(wstring textureFile)
	: Quad(textureFile)
{
	Init();

	_collider = make_shared<CircleCollider>(50);
	_collider->SetParent(GetTransform());
    _collider->SetPos(Vector(300, 0));
    _collider->GetTransform()->SetScale(Vector(0.7f, 0.7f));
    _collider->GetTransform()->SetPos(Vector(0, 0));
}

DunBullet::~DunBullet()
{
}

void DunBullet::PreUpdate()
{
    if (_isActive == false) return;

    _collider->Update();
}

void DunBullet::Update()
{
    if (_isActive == false) return;

    _time += TimeManager::Instance()->DeltaTime();

    if (_time > _lifeTime)
    {
        _time = 0.0f;
        _isActive = false;
    }

    GetTransform()->AddPos(_bulletDir * _bulletSpeed * TimeManager::Instance()->DeltaTime());

    Quad::Update();
}

void DunBullet::Render()
{
    if (_isActive == false) return;

    Quad::Render();
}

void DunBullet::PostRender()
{
    if (_isActive == false) return;

    _collider->Render();
}

void DunBullet::CreateMesh()
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

void DunBullet::SetDir(Vector dir)
{
    _bulletDir = dir.NormalVector();
}

void DunBullet::SetPos(Vector pos)
{
    GetTransform()->SetPos(pos);
}

void DunBullet::SetAngle(float angle)
{
    GetTransform()->SetAngle(angle);
}