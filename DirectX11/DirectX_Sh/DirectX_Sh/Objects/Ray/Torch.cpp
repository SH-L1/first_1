#include "framework.h"
#include "Torch.h"

Torch::Torch()
{
	//TODO: 토치 리소스 파일 추가
	_torch = make_shared<Quad>(L"");
	_collider = make_shared<RectCollider>(_torch->GetImageSize());

	_torch->GetTransform()->SetParent(_collider->GetTransform());
	_torch->Update();
}

Torch::~Torch()
{
}

void Torch::PreUpdate()
{
	if (!_isActive) return;

	_collider->Update();
}

void Torch::Update()
{
	if (!_isActive) return;

	Falling();

	_torch->Update();
}

void Torch::Render()
{
	if (!_isActive) return;
	
	_torch->Render();
}

void Torch::PostRender()
{
	if (!_isActive) return;
	
	_torch->Render();
}

void Torch::Falling()
{
	Vector moveDir = Vector(0, 0);

	_velocity.y += _gravity * DELTA_TIME;
	moveDir.y += _velocity.y * DELTA_TIME;

	_collider->GetTransform()->AddPos(moveDir);
}