#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
    _quad = make_shared<Quad>(L"Resource/SIUUUU.jpg");
    _quad2 = make_shared<Quad>(L"Resource/CryingMessi.jpg");
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
    _quad->Update();
    _quad2->Update();
}

void TutorialScene::Render()
{
    _quad->Render();
    _quad2->Render();
}
