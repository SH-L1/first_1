#include "framework.h"
#include "Ball.h"

Ball::Ball(float radius)
	: _radius(radius)
{
	_circle = make_shared<CircleCollider>(_reset, _radius);
}

Ball::~Ball()
{
}

void Ball::Update()
{
	if (_shot)
	{
		_velocity.y += _gravity;
		_circle->centre += _velocity;
	}

	_circle->Update();
}

void Ball::Render(HDC hdc)
{
	_circle->Render(hdc);
}

bool Ball::BallEnd(float floor)
{
	if (_circle->centre.y >= floor)
	{
		_shot = false;
		return true;
	}

	return false;
}