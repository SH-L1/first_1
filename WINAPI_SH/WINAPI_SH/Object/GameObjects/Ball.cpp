#include "framework.h"
#include "Ball.h"

Ball::Ball(float radius)
	: _radius(radius)
{
	_circle = make_shared<CircleCollider>(Vector2D(), _radius);
}

Ball::~Ball()
{
}

void Ball::Update()
{
	if (_isActive == false) return;

	Vector2D centre = _circle->centre;

	if (centre.x > WIN_WIDTH || centre.x < 0)
	{
		_dir.x *= -1;
		_velocity.x *= -1;
	}

	if (centre.y > WIN_HEIGHT || centre.y < 0)
	{
		_dir.y *= -1;
		_velocity.y *= -1;
	}

	_velocity.y += _gravity;
	_circle->centre += _velocity;
	
	_circle->Update();
}

void Ball::Render(HDC hdc)
{
	if (_isActive == false) return;

	_circle->Render(hdc);
}

bool Ball::BallEnd(float floor)
{
	if (_circle->centre.y >= floor)
		return true;
	
	return false;
}