#pragma once

class Block
{
public:
	Block(Vector2D halfSize);
	~Block();

	void Update();
	void Render(HDC hdc);

	void SetPos(Vector2D pos) { _block->centre = pos; }

	Vector2D GetCollisionPoint(shared_ptr<CircleCollider> energy);
	shared_ptr<Collider> GetCollider() { return _block; }

private:
	shared_ptr<RectCollider> _block;
};