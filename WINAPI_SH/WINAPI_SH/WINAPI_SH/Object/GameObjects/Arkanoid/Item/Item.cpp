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
	_item->centre += _velocity;

	_item->Update();
}

void Item::Render(HDC hdc)
{
	_item->Render(hdc);
}

bool Item::IsCollision_Bar(shared_ptr<RectCollider> bar)
{
	if (_item->IsCollision(bar))
		return true;

	return false;
}