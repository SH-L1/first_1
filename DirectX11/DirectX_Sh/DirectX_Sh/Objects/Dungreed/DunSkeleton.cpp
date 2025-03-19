#include "framework.h"
#include "DunSkeleton.h"

DunSkeleton::DunSkeleton()
{
    _skeleton = make_shared<Quad>(L"Resource/Skeleton.png");
    _collider = make_shared<RectCollider>(_skeleton->GetImageSize());

    _skeleton->GetTransform()->SetParent(_collider->GetTransform());
    _collider->GetTransform()->SetScale(Vector(0.15f, 0.2f));
    _skeleton->GetTransform()->SetScale(Vector(6, 4.5));
    
    _skeleton->GetTransform()->SetPos(Vector(0, 40));

    _collider->Update();
}

DunSkeleton::~DunSkeleton()
{
}

void DunSkeleton::PreUpdate()
{
    if (_isActive == false) return;

    _collider->Update();
}

void DunSkeleton::Update()
{
    if (_isActive == false) return;

    _skeleton->Update();
}

void DunSkeleton::Render()
{
    if (_isActive == false) return;

    _skeleton->Render();
}

void DunSkeleton::PostRender()
{
    if (_isActive == false) return;

    _collider->Render();
}

void DunSkeleton::SetActive(bool active)
{
    _isActive = active;

    if (_isActive = true)
    {
        Vector randPos = Random::RandomCord(_collider->GetWorldScale() * 0.5f);
        _collider->SetPos(randPos);

        _hp = 3;
    }
}

void DunSkeleton::TakeDamage(int damage)
{
    _hp -= damage;

    if (_hp == 0)
        _isActive = false;
}

void DunSkeleton::Move(shared_ptr<Collider> other)
{
    if (_isActive == false) return;

    Vector _skeletonPos = _collider->GetTransform()->GetWorldPos();

    Vector _dir = (other->GetWorldPos() - _skeletonPos).NormalVector();

    if (abs(other->GetWorldPos().x - _skeletonPos.x) <= 0.1f &&
        abs(other->GetWorldPos().y - _skeletonPos.y) <= 0.1f)
        return;

    _collider->GetTransform()->AddPos(_dir * _speed * DELTA_TIME);
}

bool DunSkeleton::IsCollision_Skeleton(shared_ptr<Collider> other)
{
    if (_isActive == false) return false;

    if (other->IsCollision(_collider))
        return true;

    return false;
}