#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
    _quad1 = make_shared<Quad>(L"Resource/SIUUUU.jpg");
    _quad2 = make_shared<Quad>(L"Resource/CryingMessi.jpg");

    _quad1->GetTransform()->SetPos(CENTRE);
    _quad1->GetTransform()->SetScale(Vector(300.0f, 300.0f));
    _quad1->GetTransform()->SetAngle(0.0f);

    _quad2->GetTransform()->SetPos(CENTRE - Vector(100.0f, 100.0f));
    _quad2->GetTransform()->SetScale(Vector(300.0f, 300.0f));
    _quad1->GetTransform()->SetAngle(0.0f);
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
    _quad1->GetTransform()->AddAngle(0.5f);
    _quad2->GetTransform()->AddPos(Vector(0.001f, 0.001f));

    _quad1->Update();
    _quad2->Update();
}

void TutorialScene::Render()
{
    _quad1->Render();
    _quad2->Render();
}
