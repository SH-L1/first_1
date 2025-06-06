#include "framework.h"
#include "Background.h"

Background::Background()
{
	_background = make_shared<Quad>(L"Resource/Map.png");

	_background->GetTransform()->SetPos(CENTRE);
	_background->GetTransform()->SetScale(Vector(1000.0f, 1000.0f));

	_background->Update();
}

Background::~Background()
{
}

void Background::Update()
{
	_background->Update();
}

void Background::Render()
{
	_background->Render();
}