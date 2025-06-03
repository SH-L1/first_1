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
    XMMATRIX rotatateM = XMMatrixRotationZ(_angle);
    XMMATRIX translateM = XMMatrixTranslation(_pos.x, _pos.y, 0);
    _srtMatrix = scaleM * rotatateM * translateM;

    if (_parent.expired() == false)
    {
        _srtMatrix *= _parent.lock()->GetMatrix();
    }

    _world->SetData(_srtMatrix);
    _world->Update();

    _world->SetVS(0);
}

void Transform::SetVS(int slot)
{
    _world->SetVS(slot);
}

Vector Transform::GetWorldPos()
{
    Vector result;
    result.x = _srtMatrix.r[3].m128_f32[0];
    result.y = _srtMatrix.r[3].m128_f32[1];

    return result;
}

Vector Transform::GetWorldScale()
{
    if (_parent.expired() == true)
        return _scale;

    Vector parentScale = _parent.lock()->GetWorldScale();

    return Vector(_scale.x * parentScale.x, _scale.y * parentScale.y);
}
