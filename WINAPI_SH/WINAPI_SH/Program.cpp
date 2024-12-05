#include "framework.h"
#include "Program.h"

#include "Scenes/PaintScene.h"

Program::Program()
{
	_sceneTable["PaintScene"] = make_shared<PaintScene>();

	_curScene = "PaintScene";
}

Program::~Program()
{
}

void Program::Update()
{
	_sceneTable[_curScene]->Update();
}

void Program::Render(HDC hdc)
{
	_sceneTable[_curScene]->Render(hdc);
}
