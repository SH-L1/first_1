#pragma once

class Block;
class Bar;
class Energy;

class Map : public shared_ptr<RectCollider>
{
public:
	Map();
	~Map();
	
	void Update();
	void Render(HDC hdc);
	void Move();
	
	void EnergyShooting();
	void Collision_Energy();
	float Reflect_Angle();

	bool isActive = true;

private:
	vector<shared_ptr<Block>> _blocks;
	shared_ptr<Energy> _energy;
	shared_ptr<Bar> _bar;

private:
	int _blockCount_x = 14;
	int _blockCount_y = 6;

	float _radius = 12.0f;
	
	float _barSpeed = 5.0f;
	float _energySpeed = 7.0f;
};