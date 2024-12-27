#pragma once

class Block
{
public:
	Block(Vector2D halfSize);
	~Block();

	void Update();
	void Render(HDC hdc);

	void SetPos(Vector2D pos) { _block->centre = pos; }

private:
	shared_ptr<RectCollider> _block;
};

