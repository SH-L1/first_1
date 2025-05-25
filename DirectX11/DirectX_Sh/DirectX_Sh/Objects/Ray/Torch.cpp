#include "framework.h"
#include "Torch.h"

Torch::Torch()
{
	_torch = make_shared<Quad>(L"Resource/Mario/Coin.png");
	_collider = make_shared<RectCollider>(_torch->GetImageSize());

	_torch->GetTransform()->SetParent(_collider->GetTransform());

	// 횃불 크기 키우기 (2배 확대)
	_torch->GetTransform()->SetScale(Vector(2.0f, 2.0f));
	_collider->GetTransform()->SetScale(Vector(2.0f, 2.0f));

	_rayData.screenOrigin = XMFLOAT4(WIN_WIDTH, WIN_HEIGHT, CENTRE.x, CENTRE.y);
	_rayData.lightAndShadow = XMFLOAT4(0.0f, 0.0f, 3.0f, 0.8f); // 강한 광원으로 설정
	_rayData.material = XMFLOAT4(0.3f, 0.9f, 1.0f, 32.0f); // 더 밝은 재질
	_rayData.objectCount = 1;

	_objData.pos = _collider->GetWorldPos();
	_objData.size = _torch->GetImageSize() * 2.0f;
	_objData.uvOffset = XMFLOAT2(0.0f, 0.0f);
	_objData.uvScale = XMFLOAT2(1.0f, 1.0f);
	_objData.reflectivity = 0.8f; // 높은 반사율
	_objData.type = 1; // 원형
	_objData.pad0 = 0;
	_objData.pad1 = 0;

	_torch->Update();

	OutputDebugStringA("Torch created as light source\n");
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

	// 위치 업데이트
	_objData.pos = _collider->GetWorldPos();

	// **중요: 광원 위치를 torch 위치로 업데이트**
	_rayData.lightAndShadow = XMFLOAT4(_objData.pos.x, _objData.pos.y, 3.0f, 0.8f);

	_torch->Update();

	// 디버그 출력
	char buffer[256];
	sprintf_s(buffer, "Torch light at: %.1f, %.1f\n", _objData.pos.x, _objData.pos.y);
	OutputDebugStringA(buffer);
}

void Torch::Render()
{
	if (!_isActive) return;

	// 광원 데이터 설정
	_torch->SetRayTracingData(_rayData);
	_torch->SetObjectData(_objData);

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

	if (auto ground = _ground.lock())
	{
		if (_collider->IsCollision(ground))
		{
			_velocity.y = 0;
			Vector pos = _collider->GetWorldPos();
			pos.y = ground->GetWorldPos().y + ground->GetWorldScale().y * 0.5f + _collider->GetWorldScale().y * 0.5f;
			_collider->SetPos(pos);
		}
	}
}