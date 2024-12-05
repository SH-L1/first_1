#include "framework.h"
#include "PaintScene.h"

PaintScene::PaintScene()
{
}

PaintScene::~PaintScene()
{
}

void PaintScene::Update()
{
	circle->Update();
	rect->Update();
	line->Update();
}

void PaintScene::Render(HDC hdc)
{
	circle->Render(hdc);
	rect->Render(hdc);
	line->Render(hdc);
}
