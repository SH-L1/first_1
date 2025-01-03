#include "framework.h"
#include "ArkanoidScene.h"

#include "Object/GameObjects/Arkanoid/Map.h"

ArkanoidScene::ArkanoidScene()
{
	_arkanoidMap = make_shared<Map>();
}

ArkanoidScene::~ArkanoidScene()
{
}

void ArkanoidScene::Update()
{
	_arkanoidMap->Move();
	_arkanoidMap->EnergyShooting();
	_arkanoidMap->Collision_Energy();
	_arkanoidMap->Update();
}

void ArkanoidScene::Render(HDC hdc)
{
	_arkanoidMap->Render(hdc);
}