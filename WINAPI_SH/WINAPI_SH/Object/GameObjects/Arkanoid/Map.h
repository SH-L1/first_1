#pragma once

class Block;

class Map
{
public:
	Map();
	~Map();
	
	void Update();
	void Render(HDC hdc);

private:
	vector<shared_ptr<Block>> _blocks;

private:
	int _blockCount_x = 7;
	int _blockCount_y = 3;
};

