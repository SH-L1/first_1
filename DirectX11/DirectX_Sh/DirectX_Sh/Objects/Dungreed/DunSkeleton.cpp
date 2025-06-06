#include "framework.h"
#include "DunSkeleton.h"

DunSkeleton::DunSkeleton()
{
    _skeleton = make_shared<Quad>(L"Resource/Skeleton.png");
    _collider = make_shared<RectCollider>(_skeleton->GetImageSize());

    RayTracingBuffer::Data rayData;
    rayData.screenOrigin = XMFLOAT4(WIN_WIDTH, WIN_HEIGHT, CENTRE.x, CENTRE.y);
    rayData.lightAndShadow = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
    rayData.material = XMFLOAT4(1.0f, 0.0f, 0.0f, 32.0f);
    rayData.objectCount = 1;
    _skeleton->SetRayTracingData(rayData);

    Vector imageSize = _skeleton->GetImageSize();
    Vector worldScale = _skeleton->GetTransform()->GetWorldScale();
    ObjectData objData;
    objData.pos = _collider->GetWorldPos();
    objData.size = XMFLOAT2(imageSize.x * worldScale.x, imageSize.y * worldScale.y);
    objData.uvOffset = XMFLOAT2(0.0f, 0.0f);
    objData.uvScale = XMFLOAT2(1.0f, 1.0f);
    objData.reflectivity = 0.0f;
    objData.type = 0;
    objData.pad0 = 0;
    objData.pad1 = 0;
    _skeleton->SetObjectData(objData);

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

    Vector imageSize = _skeleton->GetImageSize();
    Vector worldScale = _skeleton->GetTransform()->GetWorldScale();
    ObjectData objData;
    objData.pos = _collider->GetWorldPos();
    objData.size = XMFLOAT2(imageSize.x * worldScale.x, imageSize.y * worldScale.y);
    objData.uvOffset = XMFLOAT2(0.0f, 0.0f);
    objData.uvScale = XMFLOAT2(1.0f, 1.0f);
    objData.reflectivity = 0.0f;
    objData.type = 0;
    objData.pad0 = 0;
    objData.pad1 = 0;
    _skeleton->SetObjectData(objData);

    _skeleton->Update();
}

void DunSkeleton::Render()
{
    if (_isActive == false) return;

    _skeleton->AddColor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
    
    RayTracingBuffer::Data rayData;
    rayData.screenOrigin = XMFLOAT4(WIN_WIDTH, WIN_HEIGHT, CENTRE.x, CENTRE.y);
    rayData.lightAndShadow = XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
    rayData.material = XMFLOAT4(1.0f, 0.0f, 0.0f, 32.0f);
    rayData.objectCount = 1;
    _skeleton->SetRayTracingData(rayData);

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