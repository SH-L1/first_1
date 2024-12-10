#include "framework.h"
#include "LineScene.h"

LineScene::LineScene()
{
	_line1 = make_shared<Line>(Vector2D(100, 100), Vector2D(100, 100));
	_line2 = make_shared<Line>(Vector2D(100, 500), Vector2D(200, 500));
	// _floor = make_shared<Line>(Vector2D(0, 600), Vector2D(2000, 600));
	_floor = make_shared<Line>(Vector2D(0, 600), Vector2D(2000, 300));
}

LineScene::~LineScene()
{
}

void LineScene::Update()
{
	_line1->_end = mousePos;

	/*int shadowLength = mousePos.x - _line1->_start.x;
	_line2->_end.x = _line2->_start.x + shadowLength;*/
	
	int _xLength = mousePos.x - _line1->_start.x;
	float _slope = static_cast<float>(_floor->_end.y - _floor->_start.y) / (_floor->_end.x - _floor->_start.x);
	_line2->_end.x = _line2->_start.x + _xLength;
	_line2->_end.y = _line2->_start.y + (_xLength * _slope);

	_line1->Update();
	_line2->Update();
	_floor->Update();
}

void LineScene::Render(HDC hdc)
{
	_line1->Render(hdc);
	_line2->Render(hdc);
	_floor->Render(hdc);
}
