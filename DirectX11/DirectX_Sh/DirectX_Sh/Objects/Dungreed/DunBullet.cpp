#include "framework.h"
#include "DunBullet.h"

DunBullet::DunBullet()
{
    _bullet = make_shared<Quad>(L"Resource/Bullet.png");
	_collider = make_shared<CircleCollider>(50);
 
    _collider->GetTransform()->SetParent(_bullet->GetTransform());
    _bullet->GetTransform()->SetScale(Vector(0.1f, 0.1f));
    _collider->GetTransform()->SetScale(Vector(0.8f, 0.8f));
    _collider->SetPos(Vector(330, 0));
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

    _bullet->GetTransform()->AddPos(_bulletDir * _bulletSpeed * DELTA_TIME);
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
    _bullet->GetTransform()->SetPos(pos);
}

void DunBullet::SetAngle(float angle)
{
    _bullet->GetTransform()->SetAngle(angle);
}