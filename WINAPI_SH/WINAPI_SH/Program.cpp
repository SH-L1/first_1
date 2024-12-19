#include "framework.h"
#include "Program.h"

#include "Scenes/PaintScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/LineScene.h"
#include "Scenes/CannonScene.h"

Program::Program()
{
	_sceneTable["PaintScene"] = make_shared<PaintScene>();
	_sceneTable["CollisionScene"] = make_shared<CollisionScene>();
	_sceneTable["LineScene"] = make_shared<LineScene>();
	_sceneTable["CannonScene"] = make_shared<CannonScene>();

	_curScene = "CannonScene";
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
