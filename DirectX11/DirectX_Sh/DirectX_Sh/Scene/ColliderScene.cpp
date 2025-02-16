#include "framework.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
{
	_rect = make_shared<RectCollider>(Vector(100, 70));
	_rotatedRect = make_shared<RectCollider>(Vector(70, 70));
	_movingRect = make_shared<RectCollider>(Vector(50, 90));

	_circle = make_shared<CircleCollider>(50);
	_movingCircle = make_shared<CircleCollider>(80);

	_rect->SetPos(CENTRE);
	_rotatedRect->SetParent(_rect->GetTransform());
	_rotatedRect->SetPos(Vector(100, 100));
	_circle->SetParent(_rect->GetTransform());
	_circle->SetPos(Vector(-100, -100));

	_rotatedRect->GetTransform()->SetAngle(45);
}

ColliderScene::~ColliderScene()
{
}

void ColliderScene::PreUpdate()
{
}

void ColliderScene::Update()
{
	_movingRect->SetPos(mousePos);
	_movingCircle->SetPos(mousePos);

	_rect->Update();
	_rotatedRect->Update();
	_movingRect->Update();
	_circle->Update();
	_movingCircle->Update();
}

void ColliderScene::Render()
{
	if (_movingRect->IsCollision(_rect))
	{
		_movingCircle->SetRed();
		_movingRect->SetRed();
		_rect->SetRed();
	}
	else if (_movingRect->IsCollision(_rotatedRect, true))
	{
		_movingCircle->SetRed();
		_movingRect->SetRed();
		_rotatedRect->SetRed();
	}
	else if (_movingRect->IsCollision(_circle, true))
	{
		_movingCircle->SetRed();
		_movingRect->SetRed();
		_circle->SetRed();
	}
	else
	{
		_rect->SetGreen();
		_rotatedRect->SetGreen();
		_movingRect->SetGreen();
		_circle->SetGreen();
		_movingCircle->SetGreen();
	}

	_rect->Render();
	_rotatedRect->Render();
	_movingRect->Render();
	_circle->Render();
	_movingCircle->Render();
}

void ColliderScene::PostRender()
{
}

void ColliderScene::Input()
{
}