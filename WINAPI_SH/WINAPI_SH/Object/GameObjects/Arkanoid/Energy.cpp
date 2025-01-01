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
	_energy->Update();
}

void Energy::Render(HDC hdc)
{
	_energy->Render(hdc);
}

bool Energy::EnergyDrop()
{
	if (_energy->centre.y <= WIN_HEIGHT)
		return true;

	return false;
}