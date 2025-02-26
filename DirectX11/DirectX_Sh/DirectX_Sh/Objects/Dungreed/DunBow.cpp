#include "framework.h"
#include "DunBow.h"

DunBow::DunBow()
{
	_bow = make_shared<Quad>(L"Resource/Bow.png");
}

DunBow::~DunBow()
{
}

void DunBow::PreUpdate()
{
}

void DunBow::Update()
{
	_bow->Update();
}

void DunBow::Render()
{
	_bow->Render();
}

void DunBow::PostRender()
{
}

void DunBow::SetAim()
{
	
}