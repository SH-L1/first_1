#include "framework.h"
#include "Cannon.h"

#include "Barrel.h"
#include "Ball.h"

Cannon::Cannon()
{
	_body = make_shared<RectCollider>(Vector2D(), Vector2D(120, 70));
	_barrel = make_shared<Barrel>(150);
	_ball = make_shared<Ball>(5);
}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	Move();
	RotateBarrel();

	_body->Update();
	_barrel->Update();
}

void Cannon::Render(HDC hdc)
{
	_barrel->Render(hdc);
	_body->Render(hdc);
}

void Cannon::Move()
{
	if (GetAsyncKeyState('A') & 0x8001)
	{
		Vector2D left = Vector2D(-1, 0);
		AddPos(left * _speed);
	}

	if (GetAsyncKeyState('D') & 0x8001)
	{
		Vector2D right = Vector2D(1, 0);
		AddPos(right * _speed);
	}

	_barrel->UpdateBody(_body->centre);
}

void Cannon::RotateBarrel()
{
	if (GetAsyncKeyState('W') & 0x8001)
	{
		_angle += 0.05f;
	}

	if (GetAsyncKeyState('S') & 0x8001)
	{
		_angle -= 0.05f;
	}

	_barrel->SetDir(Vector2D(cosf(_angle), -sinf(_angle)));
}

void Cannon::Shooting()
{
	if (GetAsyncKeyState(VK_SPACE))
	{
		_ball->UpdateBody(_barrel->GetEndPoint());

		if (_ball->BallEnd())
			_ball->UpdateBody(_ball->ResetLC());
	}

	_ball->SetDir(Vector2D(cosf(_angle), -sinf(_angle)));
}