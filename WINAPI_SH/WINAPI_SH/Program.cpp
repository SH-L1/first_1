#include "framework.h"
#include "Program.h"

#include "Scenes/PaintScene.h"
#include "Scenes/CollisionScene.h"
#include "Scenes/LineScene.h"
#include "Scenes/CannonScene.h"
#include "Scenes/ArkanoidScene.h"

HDC Program::backBuffer = nullptr;

Program::Program()
{
	_sceneTable["PaintScene"] = make_shared<PaintScene>();
	_sceneTable["CollisionScene"] = make_shared<CollisionScene>();
	_sceneTable["LineScene"] = make_shared<LineScene>();
	_sceneTable["CannonScene"] = make_shared<CannonScene>();
	_sceneTable["ArkanoidScene"] = make_shared<ArkanoidScene>();

	_curScene = "ArkanoidScene";

	HDC hdc = GetDC(hWnd);

	// µµÈ­Áö
	backBuffer = CreateCompatibleDC(hdc);
	_hBitMap = CreateCompatibleBitmap(hdc, WIN_WIDTH, WIN_HEIGHT);
	SelectObject(backBuffer, _hBitMap);
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
	// ´Ù½Ã ¹è°æÀ» Èò¹ÙÅÁÀ¸·Î µ¤À½
	PatBlt(backBuffer, 0, 0, WIN_WIDTH, WIN_HEIGHT, BLACKNESS);

	_sceneTable[_curScene]->Render(backBuffer);

	BitBlt
	(
		hdc,
		0, 0,
		WIN_WIDTH,
		WIN_HEIGHT,
		backBuffer,
		0, 0,
		SRCCOPY
	);
}
