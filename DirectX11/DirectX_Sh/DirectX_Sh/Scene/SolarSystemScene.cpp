#include "framework.h"
#include "SolarSystemScene.h"

SolarSystemScene::SolarSystemScene()
{
	_sun = make_shared<Quad>(L"Resource/sun.png");
	_sun->GetTransform()->SetPos(CENTRE);

	_sunTrans = make_shared<Transform>();
	_earthTrans = make_shared<Transform>();

	_earth = make_shared<Quad>(L"Resource/earth.png");
	_earth->GetTransform()->AddPos(Vector(200, 0));
	_earth->GetTransform()->SetScale(Vector(0.5f, 0.5f));
	_earth->GetTransform()->SetParent(_sunTrans);

	_moon = make_shared<Quad>(L"Resource/moon.png");
	_moon->GetTransform()->AddPos(Vector(200, 0));
	_moon->GetTransform()->SetScale(Vector(0.2f, 0.2f));
	_moon->GetTransform()->SetParent(_earthTrans);
}

SolarSystemScene::~SolarSystemScene()
{
}

void SolarSystemScene::Update()
{
	_sun->Update();
	_earth->Update();
	_moon->Update();
	_sunTrans->Update();

	_sunTrans->SetPos(_sun->GetTransform()->GetLocalPos());
	_earthTrans->SetPos(_earth->GetTransform()->GetWorldPos());
	
	_sun->GetTransform()->AddAngle(0.0001f);
	_sunTrans->AddAngle(0.00005f);
	_earth->GetTransform()->AddAngle(0.0001f);
	_earthTrans->AddAngle(0.0001f);
}

void SolarSystemScene::Render()
{
	_sun->Render();
	_earth->Render();
	_moon->Render();
}