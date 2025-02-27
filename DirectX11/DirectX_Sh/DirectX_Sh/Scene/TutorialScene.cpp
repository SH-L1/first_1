#include "framework.h"
#include "TutorialScene.h"

#include "Objects/Dungreed/Items/DunBullet.h"

TutorialScene::TutorialScene()
{
	test = make_shared<DunBullet>();

	test->SetActive(true);
	test->SetPos(CENTRE);
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::PreUpdate()
{
	test->PreUpdate();
}

void TutorialScene::Update()
{
	test->Update();
}

void TutorialScene::Render()
{
	test->Render();
}

void TutorialScene::PostRender()
{
	test->PostRender();
}