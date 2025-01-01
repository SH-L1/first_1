#include "framework.h"
#include "Bar.h"

Bar::Bar(Vector2D halfsize)
{
	_bar = make_shared<RectCollider>(Vector2D(), halfsize * 2.0f);
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
