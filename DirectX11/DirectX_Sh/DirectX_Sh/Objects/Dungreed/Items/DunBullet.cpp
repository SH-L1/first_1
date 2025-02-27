#include "framework.h"
#include "DunBullet.h"

DunBullet::DunBullet()
{
    _bullet = make_shared<Quad>(L"Resource/Bullet.png");
	_collider = make_shared<CircleCollider>(50);

    _bullet->GetTransform()->SetParent(_collider->GetTransform());
    _bullet->GetTransform()->SetScale(Vector(1, 1));
    _collider->GetTransform()->SetScale(Vector(0.08f, 0.08f));
    _bullet->GetTransform()->SetPos(Vector(-300, 0));
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

    _time += DELTA_TIME;

    if (_time > _lifeTime)
    {
        _time = 0.0f;
        _isActive = false;
    }

    _collider->GetTransform()->AddPos(_bulletDir * _bulletSpeed * DELTA_TIME);
    _bullet->Update();
}

void DunBullet::Render()
{
    if (_isActive == false) return;

    _bullet->Render();
}

void DunBullet::PostRender()
{
    if (_isActive == false) return;

    _collider->Render();
}

void DunBullet::SetDir(Vector dir)
{
    _bulletDir = dir.NormalVector();
}

void DunBullet::SetPos(Vector pos)
{
    _collider->SetPos(pos);
}

void DunBullet::SetAngle(float angle)
{
    _collider->GetTransform()->SetAngle(angle);
}