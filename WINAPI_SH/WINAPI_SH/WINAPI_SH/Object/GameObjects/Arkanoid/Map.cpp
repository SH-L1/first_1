#include "framework.h"
#include "Map.h"

#include "Object/GameObjects/Arkanoid/Bar.h"
#include "Object/GameObjects/Arkanoid/Block.h"
#include "Object/GameObjects/Arkanoid/Energy.h"

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

	_energy = make_shared<Energy>(_radius);
	_bar = make_shared<Bar>();
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

	_bar->Update();

	if (_energy->IsActive() == false)
		_energy->StartPos(Vector2D(_bar->GetCollider()->centre.x,
			_bar->GetCollider()->centre.y - (_bar->GetSize().y + _radius)));
	else if(_energy->IsActive() == true)
		_energy->Update();
}

void Map::Render(HDC hdc)
{
	if (isActive == false) return;

	if (_energy->DeadPoint()) return;

	for (auto block : _blocks)
	{
		if (block == nullptr)
			continue;

		block->Render(hdc);
	}

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

	bool _isCollision = _energy->IsCollision_Bar(
		static_pointer_cast<RectCollider>(_bar->GetCollider()));

	if (_isCollision)
	{
		Vector2D newDir = _energy->GetDir();
		newDir.y *= -1 * Reflect_Angle();
		_energy->SetDir(newDir);
		_energy->SetVelocity(_energySpeed);

		return;
	}

	for (auto& block : _blocks)
	{
		bool _isCollision = _energy->IsCollision_Block(
			static_pointer_cast<RectCollider>(block->GetCollider()));

		if (block != nullptr && _isCollision)
		{
			Vector2D newDir = _energy->GetDir();
			newDir.y *= -1;
			_energy->SetDir(newDir);
			_energy->SetVelocity(_energySpeed);

			block = nullptr;
			
			return;
		}
	}
}

float Map::Reflect_Angle()
{
	Vector2D collisionPoint = _bar->GetCollisionPoint(
		static_pointer_cast<CircleCollider>(_energy->GetCollider()));

	float reflectionPoint = static_cast<float>(abs(
		_bar->GetCollider()->centre.x - collisionPoint.x));

	if (reflectionPoint <= _bar->GetSize().x / 3)
		return 1.0f;
	else if (reflectionPoint <= (_bar->GetSize().x / 3) * 2)
		return 1.5f;
	else
		return 2.0f;
}	