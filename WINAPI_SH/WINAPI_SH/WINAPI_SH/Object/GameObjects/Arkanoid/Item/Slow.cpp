#include "framework.h"
#include "Slow.h"

Slow::Slow()
{
	_slow = make_shared<CircleCollider>(Vector2D(), _radius);
}

Slow::~Slow()
{
}

void Slow::Update()
{
	_slow->Update();
}

void Slow::Render(HDC hdc)
{
	_slow->Render(hdc);
}

float Slow::MakeEnergySlow()
{
	time += 0.03f;
	
	if (time >= durationTime)
	{
		
	}
}

bool Slow::MissItem()
{
	return false;
}

bool Slow::IsCollision_Bar(shared_ptr<RectCollider> bar)
{
	return false;
}
