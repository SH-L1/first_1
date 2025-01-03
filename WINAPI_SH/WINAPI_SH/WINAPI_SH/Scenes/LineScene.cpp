#include "framework.h"
#include "LineScene.h"

LineScene::LineScene()
{
	_line1 = make_shared<LineCollider>(Vector2D(100, 100), Vector2D(100, 100));
	_line2 = make_shared<LineCollider>(Vector2D(100, 500), Vector2D(800, 100));
	// _floor = make_shared<LineCollider>(Vector2D(0, 600), Vector2D(2000, 600));

	_circle = make_shared<CircleCollider>(Vector2D(), 5);
}

LineScene::~LineScene()
{
}

void LineScene::Update()
{
#pragma region shadow
	// _line1->_end = mousePos;

	/* int shadowLength = mousePos.x - _line1->_start.x;
	_line2->_end.x = _line2->_start.x + shadowLength; */
	
	// int _xLength = mousePos.x - _line1->_start.x;
	// float _slope = static_cast<float>(_floor->_end.y - _floor->_start.y) / (_floor->_end.x - _floor->_start.x);
	// _line2->_end.x = _line2->_start.x + _xLength;
	// _line2->_end.y = _line2->_start.y + (_xLength * _slope);

	// _line1->Update();
	// _line2->Update();
	// _floor->Update();

	// L
	// Vector2D L = _line1->_end - _line1->_start;
	// Q
	// Vector2D Q = _line2->_end - _line2->_start;
	// float shadowLength = Q.NormalVector().DotProduct(L);

	// _line2->_end = _line2->_start + Q.NormalVector() * shadowLength;

	// ����
	// A Dot (B�� ��������) => A�� B���Ϳ� ������ ���� => Dot Projection
#pragma endregion
	
#pragma region collision
	Line::HitResult hitResult = _line1->IsCollision(_line2);
	if (hitResult.isCollision)
	{
		_line1->SetRed();
		_line2->SetRed();

		_circle->centre = hitResult.point;
	}
	else
	{
		_line1->SetGreen();
		_line2->SetGreen();
	}

	_line1->_end = mousePos;

	_line1->Update();
	_line2->Update();
	//_floor->Update();
	_circle->Update();

#pragma endregion
}

void LineScene::Render(HDC hdc)
{
	_line1->Render(hdc);
	_line2->Render(hdc);
	// _floor->Render(hdc);
}
