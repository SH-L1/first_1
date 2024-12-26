#include "framework.h"
#include "Cannon.h"

#include "Barrel.h"
#include "Ball.h"

Cannon::Cannon()
{
	_body = make_shared<RectCollider>(Vector2D(), Vector2D(120, 70));
	_barrel = make_shared<Barrel>(150);
	
	// Object Pooling
	for (int i = 0; i < _ballCount; i++)
	{
		auto ball = make_shared<Ball>(10);
		_balls.push_back(ball);
	}
}

Cannon::~Cannon()
{
}

void Cannon::Update()
{
	Move();
	RotateBarrel();
	Shooting();

	_body->Update();
	_barrel->Update();

	for(auto ball : _balls)
		ball->Update();

	for (auto& _ball : _balls)
	{
		if (_ball->BallEnd(static_cast<float>(_body->Bottom())))
		{
			_ball->SetActive(false);
		}
	}

	_timer += 0.03f;
}

void Cannon::Render(HDC hdc)
{
	_barrel->Render(hdc);
	_body->Render(hdc);

	for (auto ball : _balls)
		ball->Render(hdc);
}

void Cannon::Move()
{
	if (GetAsyncKeyState('A') & 0x8001)
	{
		Vector2D left = Vector2D(-1, 0);
		AddPos(left * _barrelspeed);
	}

	if (GetAsyncKeyState('D') & 0x8001)
	{
		Vector2D right = Vector2D(1, 0);
		AddPos(right * _barrelspeed);
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
	if (_timer < _delay) return;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		auto it = find_if(_balls.begin(), _balls.end(), [](shared_ptr<Ball> ball)->bool
			{
				if (ball->IsActive() == false)
					return true;

				return false;
			});

		if (it == _balls.end()) return;

		_timer = 0.0f;
		auto _ball = (*it);

		_ball->SetActive(true);
		_ball->UpdateBody(_barrel->GetEndPoint());
		_ball->SetDir(_barrel->GetDir());
		_ball->SetVelocity(_ballspeed * _barrel->GetBarrelLength());
		_ball->SetShot();
	}
}