#include "framework.h"
#include "Energy.h"

Energy::Energy(float radius)
{
	_energy = make_shared<CircleCollider>(Vector2D(), radius);
}

Energy::~Energy()
{
}

void Energy::Update()
{
	Vector2D centre = _energy->centre;

	if (centre.x > WIN_WIDTH || centre.x < 0)
	{
		_dir.x *= -1;
		_velocity.x *= -1;
	}

	if (centre.y < 0)
	{
		_dir.y *= -1;
		_velocity.y *= -1;
	}

	_energy->centre += _velocity;

	_energy->Update();
}

void Energy::Render(HDC hdc)
{
	_energy->Render(hdc);
}

bool Energy::DeadPoint()
{
	if (_energy->centre.y > WIN_HEIGHT)
		return true;

	return false;
}

bool Energy::IsCollision_Bar(shared_ptr<RectCollider> bar)
{
	if (_energy->IsCollision(bar))
		return true;

	return false;
}

bool Energy::IsCollision_Block(shared_ptr<RectCollider> block)
{
	if (_energy->IsCollision(block))
		return true;

	return false;
}