#include "framework.h"
#include "Block.h"

Block::Block(Vector2D halfSize)
{
	_block = make_shared<RectCollider>(Vector2D(), halfSize * 2.0f);
}

Block::~Block()
{
}

void Block::Update()
{
	_block->Update();
}

void Block::Render(HDC hdc)
{
	_block->Render(hdc);
}
