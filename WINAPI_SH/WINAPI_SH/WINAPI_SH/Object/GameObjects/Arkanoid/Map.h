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
	
	bool GameEnd();

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
	int _blockCount_x = 16;
	int _blockCount_y = 4;

	float _barSpeed = 8.0f;
	float _energySpeed = 8.0f;
	float _itemSpeed = 3.0f;

	int _slowItemBlockIndex = -1;
	int _enlargeItemBlockIndex = -1;
};