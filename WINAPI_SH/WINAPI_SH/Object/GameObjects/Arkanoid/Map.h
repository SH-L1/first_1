#pragma once

class Block;
class Bar;
class Energy;

class Map
{
public:
	Map();
	~Map();
	
	void Update();
	void Render(HDC hdc);
	void Move();

private:
	vector<shared_ptr<Block>> _blocks;
	shared_ptr<Energy> _energy;

private:
	int _blockCount_x = 14;
	int _blockCount_y = 4;
};

