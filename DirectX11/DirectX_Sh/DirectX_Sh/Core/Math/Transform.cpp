#include "framework.h"
#include "Transform.h"

Transform::Transform()
{
	_world = make_shared<MatrixBuffer>();
	_srtMatrix = XMMatrixIdentity();
}

Transform::~Transform()
{
}

void Transform::Update()
{
	XMMATRIX scaleM = XMMatrixScaling(_scale.x, _scale.y, 1);
	XMMATRIX rotationM = XMMatrixRotationZ(_angle);
	XMMATRIX translateM = XMMatrixTranslation(_pos.x, _pos.y, 0);
	_srtMatrix = scaleM * rotationM * translateM;

	if (_parent.expired() == false)
	{
		_srtMatrix *= _parent.lock()->GetMatrix();
	}

	_world->SetData(_srtMatrix);

	_world->Update();
}

void Transform::SetVS(int slot)
{
	_world->SetVS(slot);
}

Vector Transform::GetWorldPos()
{
	Vector _result;

	// За·Д
	_result.x = _srtMatrix.r[3].m128_f32[0];
	_result.y = _srtMatrix.r[3].m128_f32[1];

	return _result;
}