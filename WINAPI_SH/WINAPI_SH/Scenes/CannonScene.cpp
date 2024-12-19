#include "framework.h"

#include "Object/GameObjects/Cannon.h"

#include "CannonScene.h"

CannonScene::CannonScene()
{
	_cannon = make_shared<Cannon>();
	_cannon->SetPos(Vector2D(300, 500));
}

CannonScene::~CannonScene()
{
}

void CannonScene::Update()
{
	_cannon->Update();
}

void CannonScene::Render(HDC hdc)
{
	_cannon->Render(hdc);
}
