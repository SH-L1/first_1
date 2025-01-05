#pragma once

class Block;
class Bar;
class Energy;

class Item;

class Map
{
public:
	Map();
	~Map();
	
	void Update();
	void Render(HDC hdc);
	void Move();
	
	void EnergyShooting();
	void Collision_Energy();
	Vector2D Reflect_Angle();

	void ConditionsOfItem(Item::Type type);

	bool isActive = true;

private:
	vector<shared_ptr<Block>> _blocks;
	shared_ptr<Energy> _energy;
	shared_ptr<Bar> _bar;

	shared_ptr<Item> _enlargeItem;
	shared_ptr<Item> _slowItem;

private:
	int _blockCount_x = 14;
	int _blockCount_y = 6;
	int _blockNum = _blockCount_x * _blockCount_y;

	float _barSpeed = 8.0f;
	float _energySpeed = 7.0f;
	float _itemSpeed = 8.0f;
};