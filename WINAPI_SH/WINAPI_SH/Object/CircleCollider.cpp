#include "framework.h"
#include "CircleCollider.h"

CircleCollider::CircleCollider(Vector2D centre, float radius)
	: _radius(radius)
{
	_centre = centre;
}

void CircleCollider::Update()
{
	// ���콺 �����͸� ���ؼ� ��ӿ�ϴ� ���
	/* Vector2D direction = (mousePos - _centre).NormalVector();

	if (direction.Length() < 10) return;
	
	direction = direction.NormalVector();
	_centre = _centre + direction * 10.0f; */

	// ������ �̿��ؼ� �ε巴�� �����̴� ���
	// Linear Interporation
	_centre = (mousePos - _centre) * 0.5f + _centre;
}

void CircleCollider::Render(HDC hdc)
{
	SelectObject(hdc, _pens[_curColor]);

	int left = _centre.x - _radius;
	int right = _centre.x + _radius;
	int top = _centre.y - _radius;
	int bottom = _centre.y + _radius;
	Ellipse(hdc, left, top, right, bottom);
}
