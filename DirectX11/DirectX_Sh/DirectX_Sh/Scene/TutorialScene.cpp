#include "framework.h"
#include "TutorialScene.h"

#include "Objects/Dungreed/DunSkeleton.h"

TutorialScene::TutorialScene()
{
	test = make_shared<DunSkeleton>();

	test->SetActive(true);
	test->GetCollider()->SetPos(CENTRE);

	test->PreUpdate();
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