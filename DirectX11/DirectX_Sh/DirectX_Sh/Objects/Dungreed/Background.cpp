#include "framework.h"
#include "Background.h"

Background::Background()
{
	_background = make_shared<Quad>(L"Resource/Map.png");

	_background->GetTransform()->SetPos(CENTRE);
	_background->GetTransform()->SetScale(Vector(1.5f, 1.5f));
	_background->AddColor(XMFLOAT4(0.2f, 0.2f, 0.2f, 0.0f));
	_background->Update();
}

Background::~Background()
{
}

void Background::Render()
{
	_background->Render();
}