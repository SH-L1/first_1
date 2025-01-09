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
	Vector2D offset = Vector2D(200, 50);

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
	
	vector<int> indices(_blocks.size());
	iota(indices.begin(), indices.end(), 0);
	
	random_device rd;
	mt19937 gen(rd());
	shuffle(indices.begin(), indices.end(), gen);

	_slowItemBlockIndex = indices[0];
	_enlargeItemBlockIndex = indices[1];
}

Map::~Map()
{
}

void Map::Update()
{
	if (GameEnd()) return;

	for (auto block : _blocks)
	{
		if (block == nullptr)
			continue;

		block->Update();
	}

	ActivateEffects();
	UpdateItemEffects();
	
	if (_slowItem->IsActive() == true)
		_slowItem->Update();

	if (_enlargeItem->IsActive() == true)
		_enlargeItem->Update();		

	_bar->Update();

	if (_energy->IsActive() == true)
		_energy->Update();
	else if (_energy->IsActive() == false) 
 		_energy->StartPos(Vector2D(_bar->GetCollider()->centre.x,
			_bar->GetCollider()->centre.y - (_bar->GetSize().y + _energy->GetRadius())));
}

void Map::Render(HDC hdc)
{
	if (GameEnd()) return;

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
	if (GameEnd()) return;

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

bool Map::GameEnd()
{
	if (_energy->GetCollider()->centre.y > WIN_HEIGHT) return true;
	for (auto& block : _blocks) if (block != nullptr) return false;

	return true;
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

	for (int i = 0; i < _blocks.size(); i++)
	{
		if (_blocks[i] == nullptr)
			continue;

		bool _isCollisionWithBlock = _energy->IsCollision_Block(
			static_pointer_cast<RectCollider>(_blocks[i]->GetCollider()));

		if (_isCollisionWithBlock)
		{
			Vector2D blockPos = _blocks[i]->GetCollider()->centre;

			if (i == _slowItemBlockIndex)
			{
				_slowItem->SetActive(true);
				_slowItem->SetPos(blockPos);
				_slowItem->SetDir(Vector2D(0, 1));
				_slowItem->SetVelocity(_itemSpeed);
			}
			else if (i == _enlargeItemBlockIndex)
			{
				_enlargeItem->SetActive(true);
				_enlargeItem->SetPos(blockPos);
				_enlargeItem->SetDir(Vector2D(0, 1));
				_enlargeItem->SetVelocity(_itemSpeed);
			}

			Vector2D newDir = _energy->GetDir();
			newDir.y *= -1;
			_energy->SetDir(newDir);
			_energy->SetVelocity(_energySpeed);

			_blocks[i] = nullptr;
			return;
		}
	}
}

Vector2D Map::Reflect_Angle()
{
	Vector2D collisionPoint = _bar->GetCollisionPoint(
		static_pointer_cast<CircleCollider>(_energy->GetCollider()));

	float offset = collisionPoint.x - _bar->GetCollider()->centre.x;
	float barWidth = _bar->GetSize().x;

	float maxAngle = 50.0f;
	float halfMaxAngle = maxAngle / 2.0f;
	float angle = 0.0f;

	if (offset <= -0.6f * barWidth)
		angle = -maxAngle;
	else if (offset <= -0.15f * barWidth)
		angle = -halfMaxAngle;
	else if (offset < 0.15f * barWidth)
		angle = 0.0f;
	else if (offset < 0.6f * barWidth)
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
	if (!_slowItem->IsActive() && !_slowEffect.activation)
	{
		_slowItem->SetActive(true);
		_slowItem->SetDir(Vector2D(0, 1));
		_slowItem->SetVelocity(_itemSpeed);
	}
	
	if (!_enlargeItem->IsActive() && !_enlargeEffect.activation)
	{
		_enlargeItem->SetActive(true);
		_enlargeItem->SetDir(Vector2D(0, 1));
		_enlargeItem->SetVelocity(_itemSpeed);
	}
}

void Map::ActivateEffects()
{
	if (_slowItem->IsActive() &&
		_slowItem->IsCollision_Bar(static_pointer_cast<RectCollider>(_bar->GetCollider())))
	{
		_slowEffect.activation = true;
		_slowItem->SetActive(false);
		_slowEffect.time = 0.0f;
		_slowEffect.durationTime = 30.0f;
		_energySpeed *= 0.5f;
		_energy->SetVelocity(_energySpeed);
	}

	if (_enlargeItem->IsActive() &&
		_enlargeItem->IsCollision_Bar(static_pointer_cast<RectCollider>(_bar->GetCollider())))
	{
		_enlargeEffect.activation = true;
		_enlargeItem->SetActive(false);
		_enlargeEffect.time = 0.0f;
		_enlargeEffect.durationTime = 30.0f;
		_bar->ResizeBar(2.0f);
	}
}

void Map::UpdateItemEffects()
{
	if (_slowEffect.activation)
	{
		_slowEffect.time += 0.016f;

		if (_slowEffect.time >= _slowEffect.durationTime)
		{
			_slowEffect.activation = false;
			_energySpeed *= 2.0f;
			_energy->SetVelocity(_energySpeed);
		}
	}

	if (_enlargeEffect.activation)
	{
		_enlargeEffect.time += 0.016f;

		if (_enlargeEffect.time >= _enlargeEffect.durationTime)
		{
			_enlargeEffect.activation = false;
			_bar->ResizeBar(0.5f);
		}
	}
}