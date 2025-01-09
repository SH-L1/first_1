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

Vector2D Block::GetCollisionPoint(shared_ptr<CircleCollider> energy)
{
    if (_block->IsCollision(energy))
    {
        Vector2D closestPoint = _block->GetClosestPoint(energy->centre);

        Vector2D direction = closestPoint - energy->centre;
        direction.Normalize();

        Vector2D collisionPoint = energy->centre + direction * energy->GetRadius();

        return collisionPoint;
    }

	return Vector2D();
}
