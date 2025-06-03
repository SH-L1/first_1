#include "framework.h"
#include "Wall.h"

Wall::Wall()
{
    _wall = make_shared<Quad>(L"Resource/Mario/GroundBlock.png");
    _collider = make_shared<RectCollider>(_wall->GetImageSize());

    _wall->GetTransform()->SetParent(_collider->GetTransform());

    _wall->GetTransform()->SetScale(_textureScale);
    _collider->GetTransform()->SetScale(_colliderScale);
}

Wall::~Wall()
{
}

void Wall::PreUpdate()
{
    _collider->Update();
}

void Wall::Update()
{
    _wall->Update();
}

void Wall::Render()
{
    _wall->Render();
}

void Wall::PostRender()
{
    _collider->SetColor(XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
    _collider->Render();
}