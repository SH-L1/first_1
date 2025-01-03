	#include "framework.h"
	#include "RectCollider.h"

	RectCollider::RectCollider(Vector2D centre, Vector2D size)
		: _halfSize(size * 0.5f)
	{
		this->centre = centre;
	}

	RectCollider::~RectCollider()
	{
	}

	void RectCollider::Update()
	{
	}

	void RectCollider::Render(HDC hdc)
	{
		SelectObject(hdc, _pens[_curColor]);

		Rectangle(hdc, Left(), Top(), Right(), Bottom());
	}

	bool RectCollider::IsCollision(const Vector2D& pos)
	{
		if (pos.x > Right()) return false;
		if (pos.x < Left()) return false;
		if (pos.y > Bottom()) return false;
		if (pos.y < Top()) return false;

		return true;
	}

	bool RectCollider::IsCollision(shared_ptr<RectCollider> other)
	{
		if (Right() < other->Left()) return false;
		if (Left() > other->Right()) return false;
		if (Bottom() < other->Top()) return false;
		if (Top() > other->Bottom()) return false;

		return true;
	}

	// AABB 충돌
	bool RectCollider::IsCollision(shared_ptr<CircleCollider> other)
	{
		Vector2D circleCentre = other->centre;
		float radius = other->GetRadius();
		float length = (circleCentre - centre).Length();

		// 위 아래 충돌체크
		if (circleCentre.x < Right() && circleCentre.x > Left())
		{
			float result = 0.0f;
			if (circleCentre.y > centre.y) // circle이 아래쪽에있다.
				result = circleCentre.y - centre.y;
			else
				result = centre.y - circleCentre.y;

			return result < radius + _halfSize.y;
		}

		// 좌우 충돌체크
		if (circleCentre.y < Bottom() && circleCentre.y > Top())
		{
			float result = 0.0f;
			if (circleCentre.x > centre.x) // circle이 오른쪽에 있다.
				result = circleCentre.x - centre.x;
			else
				result = centre.x - circleCentre.x;

			return result < radius + _halfSize.x;
		}

		// 각 꼭지점 체크
		Vector2D leftTop = Vector2D(Left(), Top());
		Vector2D rightTop = Vector2D(Right(), Top());
		Vector2D leftBottom = Vector2D(Left(), Bottom());
		Vector2D rightBottom = Vector2D(Right(), Bottom());

		bool check1 = other->IsCollision(leftTop);
		bool check2 = other->IsCollision(rightTop);
		bool check3 = other->IsCollision(leftBottom);
		bool check4 = other->IsCollision(rightBottom);

		return check1 || check2 || check3 || check4;
	}

	Vector2D RectCollider::GetClosestPoint(const Vector2D& point)
	{
		float closestX = max(Left(), min(point.x, Right()));
		float closestY = max(Top(), min(point.y, Bottom()));

		return Vector2D(closestX, closestY);
	}