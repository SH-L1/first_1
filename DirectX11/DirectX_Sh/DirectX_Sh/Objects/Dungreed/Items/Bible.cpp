#include "framework.h"
#include "Bible.h"

Bible::Bible()
{
	_bible = make_shared<Quad>(L"Resource/Bible.png");
	_collider = make_shared<RectCollider>(_bible->GetImageSize());

	_bible->GetTransform()->SetParent(_collider->GetTransform());
	_bible->GetTransform()->SetScale(Vector(1.5f, 1.5f));
}

Bible::~Bible()
{
}

void Bible::PreUpdate()
{
	if (_isActive == false) return;

	_collider->Update();
}

void Bible::Update()
{
	if (_isActive == false) return;

	_bible->Update();
}

void Bible::Render()
{
	if (_isActive == false) return;

	_bible->Render();
}

void Bible::PostRender()
{
	if (_isActive == false) return;

	_collider->Render();
}