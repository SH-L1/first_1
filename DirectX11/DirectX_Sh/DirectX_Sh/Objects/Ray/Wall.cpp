#include "framework.h"
#include "Wall.h"

Wall::Wall()
{
    _wall = make_shared<Quad>(L"Resource/Mario/GroundBlock.png");
    _collider = make_shared<RectCollider>(_wall->GetImageSize());

    _wall->GetTransform()->SetParent(_collider->GetTransform());
    _wall->GetTransform()->SetScale(Vector(8.0f, 8.0f));
    _collider->GetTransform()->SetScale(Vector(10.0f, 5.0f));
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
    _collider->Render();
}