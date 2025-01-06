#include "framework.h"
#include "Item.h"

Item::Item(Type type)
	: _type(type)
{
	_item = make_shared<CircleCollider>(Vector2D(), _radius);
}

Item::~Item()
{
}

void Item::Update()
{
	if (_isActive == false) return;
	
	if (_item->centre.y >= WIN_HEIGHT)
	{
		_isActive = false;
		
		return;
	}

	_item->centre += _velocity;

	_item->Update();
}

void Item::Render(HDC hdc)
{
	if (_isActive == false) return;

	_item->Render(hdc);
}

void Item::StartPos()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(_radius * 3, WIN_WIDTH - (_radius * 3));

	Vector2D randomPos;
	randomPos.x = static_cast<float>(dis(gen));
	randomPos.y = 0.0f - _radius;

	_item->centre = randomPos;
}

bool Item::IsCollision_Bar(shared_ptr<RectCollider> bar)
{
	if (_item->IsCollision(bar))
		return true;

	return false;
}