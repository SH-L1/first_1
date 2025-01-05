#include "framework.h"
#include "Bar.h"

Bar::Bar()
{
	_bar = make_shared<RectCollider>(Vector2D(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.75f), _halfsize * 2.0f);
}

Bar::~Bar()
{
}

void Bar::Update()
{
	_bar->Update();
}

void Bar::Render(HDC hdc)
{
	_bar->Render(hdc);
}

void Bar::ResizeBar(float addsize)
{
    _halfsize.x *= addsize;

    _bar = make_shared<RectCollider>(_bar->centre, _halfsize * 2.0f);
}

Vector2D Bar::GetCollisionPoint(shared_ptr<CircleCollider> energy)
{
    if (_bar->IsCollision(energy))
    {
        Vector2D closestPoint = _bar->GetClosestPoint(energy->centre);

        Vector2D direction = closestPoint - energy->centre;
        direction.Normalize();

        Vector2D collisionPoint = energy->centre + direction * energy->GetRadius();

        return collisionPoint;
    }

	return Vector2D();
}
