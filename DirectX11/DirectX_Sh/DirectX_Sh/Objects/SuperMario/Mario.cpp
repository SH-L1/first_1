#include "framework.h"
#include "Mario.h"

Mario::Mario()
{
	_mario = make_shared<Quad>(L"Resource/");
}

Mario::~Mario()
{
}

void Mario::PreUpdate()
{
}

void Mario::Update()
{
}

void Mario::Render()
{
}

void Mario::PostRender()
{
}
