#include "framework.h"

#include "Object/GameObjects/Cannon.h"

#include "CannonScene.h"

CannonScene::CannonScene()
{
	_cannon = make_shared<Cannon>(100, 20);
	_rivalcannon = make_shared<Cannon>(100, 20);

	_cannon->SetPos(Vector2D(300, 500));
	_rivalcannon->SetPos(Vector2D(1600, 500));

	_cannon->Update();
	_rivalcannon->Update();

	_cannon->Move();
	_rivalcannon->Move();
}

CannonScene::~CannonScene()
{
}

void CannonScene::Update()
{
	if (_turn)
	{
		_cannon->Move();
		_cannon->RotateBarrel();
		_cannon->Shooting(_turn);
	}
	else
	{
		_rivalcannon->Move();
		_rivalcannon->RotateBarrel();
		_rivalcannon->Shooting(_turn);
	}

	_cannon->Update();
	_rivalcannon->Update();

	for (auto ball : _cannon->GetBalls())
	{
		_rivalcannon->IsCollision_Ball(ball);
	}

	for (auto ball : _rivalcannon->GetBalls())
	{
		_cannon->IsCollision_Ball(ball);
	}
}

void CannonScene::Render(HDC hdc)
{
	_cannon->Render(hdc);
	_rivalcannon->Render(hdc);
}
