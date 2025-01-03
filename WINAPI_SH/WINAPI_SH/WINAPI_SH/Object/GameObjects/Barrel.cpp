#include "framework.h"
#include "Barrel.h"

Barrel::Barrel(float length)
	: _length(length)
{
	_line = make_shared<LineCollider>(Vector2D(), Vector2D());
}

Barrel::~Barrel()
{
}

void Barrel::Update()
{
	_line->_end = _line->_start + _dir * _length;

	_line->Update();
}

void Barrel::Render(HDC hdc)
{
	_line->Render(hdc);
}