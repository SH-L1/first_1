#include "framework.h"
#include "Map.h"

#include "Object/GameObjects/Arkanoid/Bar.h"
#include "Object/GameObjects/Arkanoid/Block.h"
#include "Object/GameObjects/Arkanoid/Energy.h"

#include "Object/GameObjects/Arkanoid/Item/Item.h"

Map::Map()
{
	Vector2D blockHalf = { 50.0f, 20.0f };
	Vector2D gap(blockHalf.x * 2 + 3, blockHalf.y * 2 + 1);
	Vector2D offset = Vector2D(250, 50);

	for (int y = 0; y < _blockCount_y; y++)
	{
		for (int x = 0; x < _blockCount_x; x++)
		{
			shared_ptr<Block> block = make_shared<Block>(blockHalf);

			float gapX = gap.x * x;
			float gapY = gap.y * y;

			Vector2D pos = Vector2D(gapX, gapY) + offset;
			block->SetPos(pos);
			_blocks.push_back(block);
		}
	}

	_energy = make_shared<Energy>();
	_bar = make_shared<Bar>();

	_slowItem = make_shared<Item>(Item::Type::Slow);
	_enlargeItem = make_shared<Item>(Item::Type::Enlarge);
}

Map::~Map()
{
}

void Map::Update()
{
	if (isActive == false) return;

	if (_energy->DeadPoint()) return;

	for (auto block : _blocks)
	{
		if (block == nullptr)
			continue;

		block->Update();
	}

	CheckItemConditions();
	
	if (_slowItem->IsActive() == true)
		_slowItem->Update();

	if (_enlargeItem->IsActive() == true)
		_enlargeItem->Update();		
	
	ActivateEffects();
	UpdateItemEffects();

	_bar->Update();

	if (_energy->IsActive() == true)
		_energy->Update();
	else if (_energy->IsActive() == false) 
 		_energy->StartPos(Vector2D(_bar->GetCollider()->centre.x,
			_bar->GetCollider()->centre.y - (_bar->GetSize().y + _energy->GetRadius())));
}

void Map::Render(HDC hdc)
{
	if (isActive == false) return;

	for (auto block : _blocks)
	{
		if (block == nullptr)
			continue;

		block->Render(hdc);
	}

	if (_slowItem->IsActive() == true)
		_slowItem->Render(hdc);

	if (_enlargeItem->IsActive() == true)
		_enlargeItem->Render(hdc);

	_bar->Render(hdc);
	_energy->Render(hdc);
}

void Map::Move()
{
	if (GetAsyncKeyState('A') & 0x8001)
	{
		Vector2D left = Vector2D(-1, 0);
		_bar->AddPos(left * _barSpeed);
	}

	if (GetAsyncKeyState('D') & 0x8001)
	{
		Vector2D right = Vector2D(1, 0);
		_bar->AddPos(right * _barSpeed);
	}

	_bar->UpdateBar(_bar->GetCollider()->centre);
}

void Map::EnergyShooting()
{
	if (_energy->IsActive() == true) return;

	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		_energy->SetActive(true);
		_energy->SetDir(Vector2D(0, -1));
		_energy->SetVelocity(_energySpeed);
	}
}

void Map::Collision_Energy()
{
	if (_energy->IsActive() == false) return;

	bool _isCollisionWithBar = _energy->IsCollision_Bar(
		static_pointer_cast<RectCollider>(_bar->GetCollider()));

	if (_isCollisionWithBar)
	{
		Vector2D newDir = Reflect_Angle();
		
		_energy->SetDir(newDir);
		_energy->SetVelocity(_energySpeed);

		return;
	}

	for (auto& block : _blocks)
	{
		if (block != nullptr)
		{
			bool _isCollisionWithBlock = _energy->IsCollision_Block(
				static_pointer_cast<RectCollider>(block->GetCollider()));

			if (_isCollisionWithBlock)
			{
				Vector2D newDir = _energy->GetDir();
				newDir.y *= -1;
				_energy->SetDir(newDir);
				_energy->SetVelocity(_energySpeed);

				block = nullptr;
				_blockNum -= 1;

				return;
			}
		}
	}
}

Vector2D Map::Reflect_Angle()
{
	Vector2D collisionPoint = _bar->GetCollisionPoint(static_pointer_cast<CircleCollider>(_energy->GetCollider()));

	float offset = collisionPoint.x - _bar->GetCollider()->centre.x;
	float sectionWidth = _bar->GetSize().x / 2.5f;

	float maxAngle = 50.0f;
	float halfMaxAngle = maxAngle / 2.0f;
	float angle = 0.0f;

	if (offset < -2 * sectionWidth)
		angle = -maxAngle;
	else if (offset >= -2 * sectionWidth && offset < -sectionWidth)
		angle = -halfMaxAngle;
	else if (offset >= -sectionWidth && offset < sectionWidth)
		angle = 0.0f;
	else if (offset >= sectionWidth && offset < 2 * sectionWidth)
		angle = halfMaxAngle;
	else
		angle = maxAngle;

	float newAngle = angle * (3.14f / 180.0f);

	Vector2D newDir(sin(newAngle), -cos(newAngle));
	newDir.Normalize();

	return newDir;
}

void Map::CheckItemConditions()
{
	int itemRequirement = (_blockCount_x * _blockCount_y) / 3;

	if (_blockNum == itemRequirement * 2)
	{
		if (!_slowItem->IsActive() && !_slowEffect.activation)
		{
			_slowItem->SetActive(true);
			_slowItem->StartPos();
			_slowItem->SetDir(Vector2D(0, 1));
			_slowItem->SetVelocity(_itemSpeed);
		}
	}

	if (_blockNum == itemRequirement)
	{
		if (!_enlargeItem->IsActive() && !_enlargeEffect.activation)
		{
			_enlargeItem->SetActive(true);
			_enlargeItem->StartPos();
			_enlargeItem->SetDir(Vector2D(0, 1));
			_enlargeItem->SetVelocity(_itemSpeed);
		}
	}
}

void Map::ActivateEffects()
{
	if (_slowItem->IsActive() && _slowItem->IsCollision_Bar(static_pointer_cast<RectCollider>(_bar->GetCollider())))
	{
		_slowEffect.activation = true;
		_slowItem->SetActive(false);
		_slowEffect.time = 0.0f;
		_slowEffect.durationTime = 5.0f;
		_energy->SetVelocity(_energySpeed * 0.5f);
	}

	if (_enlargeItem->IsActive() && _enlargeItem->IsCollision_Bar(static_pointer_cast<RectCollider>(_bar->GetCollider())))
	{
		_enlargeEffect.activation = true;
		_enlargeItem->SetActive(false);
		_enlargeEffect.time = 0.0f;
		_enlargeEffect.durationTime = 10.0f;
		_bar->ResizeBar(10.0f);
	}
}

void Map::UpdateItemEffects()
{
	if (_slowEffect.activation)
	{
		_slowEffect.time += 0.016f;

		if (_slowEffect.time >= 5.0f)
		{
			_slowEffect.activation = false;
			_energy->SetVelocity(_energySpeed);
		}
	}

	if (_enlargeEffect.activation)
	{
		_enlargeEffect.time += 0.016f;

		if (_enlargeEffect.time >= 10.0f)
		{
			_enlargeEffect.activation = false;
			_bar->ResizeBar(1.5f);
		}
	}
}