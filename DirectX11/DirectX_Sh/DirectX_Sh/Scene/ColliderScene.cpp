#include "framework.h"
#include "ColliderScene.h"

ColliderScene::ColliderScene()
{
	_rect1 = make_shared<RectCollider>(Vector(100.0f, 100.0f));
	_rect2 = make_shared<RectCollider>(Vector(120.0f, 80.0f));
	_circle1 = make_shared<CircleCollider>(100.0f);
	_circle2 = make_shared<CircleCollider>(120.0f);

	_rect1->GetTransform()->SetScale(Vector(1.5f, 1.5f));
	_circle1->GetTransform()->SetScale(Vector(2.0f, 2.0f));

	_rect1->SetPos(CENTRE);
	_rect2->SetPos(CENTRE * 0.25f);
	_circle1->GetTransform()->SetPos(Vector(800.0f, 450.0f));
}

ColliderScene::~ColliderScene()
{
}

void ColliderScene::Update()
{
	_circle2->SetPos(MOUSE_POS);

	if (KEY_PRESS('W'))
		_rect1->GetTransform()->AddPos(Vector(0.0f, 5.0f) * DELTA_TIME);
	if (KEY_PRESS('S'))
		_rect1->GetTransform()->AddPos(Vector(0.0f, -5.0f) * DELTA_TIME);
	if (KEY_PRESS('A'))
		_rect1->GetTransform()->AddPos(Vector(-5.0f, 0.0f) * DELTA_TIME);
	if (KEY_PRESS('D'))
		_rect1->GetTransform()->AddPos(Vector(5.0f, 0.0f) * DELTA_TIME);

	if (_circle2->IsCollision(_rect1))
	{
		_rect1->SetRed();
		_circle2->SetRed();
	}
	else if (_circle2->IsCollision(_rect2))
	{
		_rect2->SetColor(BLUE);
		_circle2->SetColor(BLUE);
	}
	else if (_circle2->IsCollision(_circle1))
	{
		_rect2->SetGreen();
		_circle2->SetGreen();
	}
	else
	{
		_rect1->SetColor(WHITE);
		_rect2->SetColor(WHITE);
		_circle1->SetColor(WHITE);
		_circle2->SetColor(WHITE);
	}

	_rect1->Update();
	_rect2->Update();
	_circle1->Update();
	_circle2->Update();
}

void ColliderScene::Render()
{
	_rect1->Render();
	_rect2->Render();
	_circle1->Render();
	_circle2->Render();
}