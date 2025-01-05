#include "framework.h"
#include "Item.h"

Item::Item(Type type)
	: _type(type)
{
	_item = make_shared<CircleCollider>(Vector2D(), _radius);

	switch (_type)
	{
	case Type::Slow:
		_durationTime = 5.0f;
		break;
	case Type::Enlarge:
		_durationTime = 10.0f;
		break;
	default:
		break;
	}
}

Item::~Item()
{
}

void Item::Update()
{
	if (_isActive == false) return;

	if (MissItem() == true) return;

	_item->Update();
}

void Item::Render(HDC hdc)
{
	if (_isActive == false) return;

	if (MissItem() == true) return;

	_item->Render(hdc);
}

void Item::StartPos()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(50, WIN_WIDTH - 50);

	Vector2D randomPos;
	randomPos.x = static_cast<float>(dis(gen));
	randomPos.y = 0.0f - _item->GetRadius();

	_item->centre = randomPos;
}

bool Item::MissItem()
{
	if (_item->centre.y >= WIN_HEIGHT)
		return true;

	return false;
}

float Item::ItemUtil()
{
	time += 0.03f;

	if (time >= _durationTime)
	{
		SetActive(false);

		return 1.0f;
	}

	switch (_type)
	{
	case Type::Slow:
		return 2.0f;
	case Type::Enlarge:
		return 1.5f;
	default:
		return 1.0f;
	}
}

bool Item::IsCollision_Bar(shared_ptr<RectCollider> bar)
{
	if (_item->IsCollision(bar))
		return true;

	return false;
}