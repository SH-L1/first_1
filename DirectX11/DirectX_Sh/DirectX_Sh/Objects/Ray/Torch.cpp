#include "framework.h"
#include "Torch.h"

Torch::Torch()
{
    _torch = make_shared<Quad>(L"Resource/Torch.png");
    _collider = make_shared<RectCollider>(_torch->GetImageSize());

    _torch->GetTransform()->SetParent(_collider->GetTransform());
    _collider->GetTransform()->SetScale(_colliderScale);
    _torch->GetTransform()->SetScale(_textureScale);

    _collider->Update();

    _rayData.screenOrigin = XMFLOAT4(WIN_WIDTH, WIN_HEIGHT, CENTRE.x, CENTRE.y);
    _rayData.lightAndShadow = XMFLOAT4(CENTRE.x, CENTRE.y, 3.0f, 0.8f);
    _rayData.material = XMFLOAT4(0.3f, 0.9f, 1.0f, 32.0f);
    _rayData.objectCount = 1;

    Vector imageSize = _torch->GetImageSize();

    _objData.pos = _collider->GetWorldPos();
    _objData.size = Vector(imageSize.x * _colliderScale.x * _textureScale.x,
        imageSize.y * _colliderScale.y * _textureScale.y);
    _objData.uvOffset = XMFLOAT2(0.0f, 0.0f);
    _objData.uvScale = XMFLOAT2(1.0f, 1.0f);
    _objData.reflectivity = 0.8f;
    _objData.type = 1;
    _objData.pad0 = 0;
    _objData.pad1 = 0;

    _torch->Update();
}

Torch::~Torch()
{
}

void Torch::PreUpdate()
{
    if (!_isActive) return;

    if (_isPickedUp)
    {
        _collider->GetTransform()->Update();
    }
    
    _collider->Update();
}

void Torch::Update()
{
    if (!_isActive) return;

    if (!_isPickedUp)
    {
        Falling();
    }

    _objData.pos = _collider->GetWorldPos();
    _rayData.lightAndShadow = XMFLOAT4(_objData.pos.x, _objData.pos.y, 3.0f, 0.8f);
    
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

    _collider->Render();
}

void Torch::Falling()
{
    Vector moveDir = Vector(0, 0);

    _velocity.y -= _gravity * DELTA_TIME;
    moveDir.y += _velocity.y * DELTA_TIME;

    _collider->GetTransform()->AddPos(moveDir);

    for (auto& ground : _grounds)
    {
        if (_collider->IsCollision(ground) && _velocity.y <= 0.0f)
        {
            float torchBottom = _collider->GetWorldPos().y - _collider->GetWorldScale().y * 0.5f;
            float groundTop = ground->GetWorldPos().y + ground->GetWorldScale().y * 0.5f;

            if (torchBottom <= groundTop + 5.0f)
            {
                _velocity.y = 0;
                Vector pos = _collider->GetWorldPos();
                pos.y = groundTop + _collider->GetWorldScale().y * 0.5f;
                _collider->SetPos(pos);
                break;
            }
        }
    }
}