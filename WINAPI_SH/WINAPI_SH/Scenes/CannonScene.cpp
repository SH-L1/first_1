#include "framework.h"

#include "Object/GameObjects/Cannon.h"

#include "CannonScene.h"

CannonScene::CannonScene()
{
	_cannon = make_shared<Cannon>(100, 10);
	_rivalcannon = make_shared<Cannon>(100, 10);
	_cannon->SetPos(Vector2D(300, 500));
	_rivalcannon->SetPos(Vector2D(1600, 500));
	_rivalcannon->SetBD(Vector2D(-1, 0));
}

CannonScene::~CannonScene()
{
}

void CannonScene::Update()
{
	switch (_turn)
	{
	case 1:
		_cannon->Update();
		break;
	case 2:
		_rivalcannon->Update();
		break;
	}
}

void CannonScene::Render(HDC hdc)
{
	_cannon->Render(hdc);
	_rivalcannon->Render(hdc);
}
