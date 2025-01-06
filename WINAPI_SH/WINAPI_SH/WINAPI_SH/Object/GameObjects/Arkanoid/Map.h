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

	void CheckItemConditions();
	void ActivateEffects();
	void UpdateItemEffects();
	
private:
	struct ItemEffect
	{
		bool activation = false;
		float time = 0.0f;
		float durationTime = 0.0f;
	};

	ItemEffect _slowEffect;
	ItemEffect _enlargeEffect;

private:
	vector<shared_ptr<Block>> _blocks;
	shared_ptr<Energy> _energy;
	shared_ptr<Bar> _bar;

	shared_ptr<Item> _enlargeItem;
	shared_ptr<Item> _slowItem;

private:
	bool isActive = true;

	int _blockCount_x = 3;
	int _blockCount_y = 1;
	int _blockNum = _blockCount_x * _blockCount_y;

	float _barSpeed = 8.0f;
	float _energySpeed = 7.0f;
	float _itemSpeed = 8.0f;
};