#include "framework.h"
#include "Cannon.h"

#include "Barrel.h"
#include "Ball.h"

Cannon::Cannon()
	: _hp(0), _atk(0)
{
}

Cannon::Cannon(int hp, int atk)
	: _hp(hp), _atk(atk)
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
	if (isActive == false) return;

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
}

void Cannon::Render(HDC hdc)
{
	if (isActive == false) return;

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

void Cannon::Shooting(bool& turn)
{
	_timer += 0.03f;

	if (_timer < _delay) return;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		_holdTime += 0.03f;
		
		if (_holdTime > 2.0f)
			_holdTime = 2.0f;
	}
	else
	{
		if (_holdTime > 0.0f)
		{
			auto it = FindActiveBall();

			if (it == nullptr) return;

			_timer = 0.0f;
			auto _ball = it;

			_ball->SetActive(true);
			_ball->UpdateBody(_barrel->GetEndPoint());
			_ball->SetDir(_barrel->GetDir());
			_ball->SetVelocity(_ballspeed * _barrel->GetBarrelLength() * _holdTime);
			turn = !turn;
		}

		_holdTime = 0.0f;
	}
}

shared_ptr<Ball> Cannon::FindActiveBall()
{
	auto it = find_if(_balls.begin(), _balls.end(), [](shared_ptr<Ball> ball)->bool
		{
			if (ball->IsActive() == false)
				return true;

			return false;
		});

	if (it == _balls.end())
	{
		for (auto& iter : _balls)
		{
			iter->SetActive(false);
		}

		return nullptr;
	}

	return *it;
}

bool Cannon::IsCollision_Ball(shared_ptr<Ball> ball)
{
	if (ball->IsActive() == false)
		return false;

	if (isActive == false)
		return false;

	if (_body->Collider::IsCollision(ball->GetCollider()))
	{
		TakeDamage(_atk);
		ball->SetActive(false);

		return true;
	}

	return false;
}

void Cannon::TakeDamage(int amount)
{
	_hp -= amount;

	if (_hp <= 0)
	{
		isActive = false;
		_hp = 0;
	}
}