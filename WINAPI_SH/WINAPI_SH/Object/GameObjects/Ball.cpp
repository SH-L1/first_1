#include "framework.h"
#include "Ball.h"

Ball::Ball(float radius)
	: _radius(radius)
{
	_circle = make_shared<CircleCollider>(Vector2D(-_radius, -_radius), _radius);
}

Ball::~Ball()
{
}

void Ball::Update()
{
	_circle->centre += _dir * _speed;

	_circle->Update();
}

void Ball::Render(HDC hdc)
{
	_circle->Render(hdc);
}

bool Ball::BallEnd()
{
	if (_circle->centre > Vector2D(1000, 1000) || _circle->centre < Vector2D(-1000, -1000))
		return true;
}