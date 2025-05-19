#include "framework.h"
#include "Wall.h"

Wall::Wall()
{
	_wall = make_shared<Quad>(L"");
	_collider = make_shared<RectCollider>(_wall->GetImageSize());
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