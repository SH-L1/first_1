#include "framework.h"

#include "Object/GameObjects/Cannon.h"

#include "CannonScene.h"

CannonScene::CannonScene()
{
	_cannon = make_shared<Cannon>();
	_rivalcannon = make_shared<Cannon>();
	_cannon->SetPos(Vector2D(300, 500));
	_rivalcannon->SetPos(Vector2D(1600, 500));
}

CannonScene::~CannonScene()
{
}

void CannonScene::Update()
{
	_cannon->Update();
	_rivalcannon->Update();
}

void CannonScene::Render(HDC hdc)
{
	_cannon->Render(hdc);
	_rivalcannon->Render(hdc);
}
