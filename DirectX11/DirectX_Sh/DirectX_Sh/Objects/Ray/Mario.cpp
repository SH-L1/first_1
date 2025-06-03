#include "framework.h"
#include "Mario.h"

Mario::Mario()
{
    _player = make_shared<Quad>(L"Resource/Mario/Mario_Big_Idle.png");
    _collider = make_shared<RectCollider>(_player->GetImageSize());
    _equipment = make_shared<Transform>();

    _collider->SetPos(CENTRE);
    _collider->Update();

    _player->GetTransform()->SetParent(_collider->GetTransform());
    _player->GetTransform()->SetScale(_textureScale);
    _collider->GetTransform()->SetScale(_colliderScale);

    _equipment->SetParent(_collider->GetTransform());
    _equipment->SetPos(Vector(0.0f, 1.0f));

    _rayData.screenOrigin = XMFLOAT4(WIN_WIDTH, WIN_HEIGHT, CENTRE.x, CENTRE.y);
    _rayData.lightAndShadow = XMFLOAT4(100.0f, 100.0f, 1.0f, 0.5f);
    _rayData.material = XMFLOAT4(0.4f, 0.8f, 1.0f, 32.0f);
    _rayData.objectCount = 1;

    Vector imageSize = _player->GetImageSize();

    _objData.pos = _collider->GetWorldPos();
    _objData.size = Vector(imageSize.x * _colliderScale.x * _textureScale.x,
        imageSize.y * _colliderScale.y * _textureScale.y);
    _objData.uvOffset = XMFLOAT2(0.0f, 0.0f);
    _objData.uvScale = XMFLOAT2(1.0f, 1.0f);
    _objData.reflectivity = 0.5f;
    _objData.type = 0;
    _objData.pad0 = 0;
    _objData.pad1 = 0;

    _player->AddColor(XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f));
    _player->SetLeftRight(0);

    _player->Update();
}

Mario::~Mario()
{
}

void Mario::PreUpdate()
{
    _collider->Update();
    _collider->GetTransform()->Update();
}

void Mario::Update()
{
    Input();
    _objData.pos = _collider->GetWorldPos();
    _player->Update();
}

void Mario::Render()
{
    _player->SetRayTracingData(_rayData);
    _player->SetObjectData(_objData);
    _player->Render();
}

void Mario::PostRender()
{
    _collider->SetColor(XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
    _collider->Render();
}

void Mario::Input()
{
    Move();

    if (!_isEquip)
    {
        Pick();
    }
}

void Mario::Move()
{
    Vector moveDir = Vector(0, 0);
    Vector curPos = _collider->GetWorldPos();
    Vector space = _collider->GetWorldScale() * 0.5f;

    if (KEY_PRESS('A'))
    {
        if (curPos.x > space.x)
            moveDir.x -= _playerSpeed * DELTA_TIME;
        _player->SetLeftRight(1);
    }
    if (KEY_PRESS('D'))
    {
        if (curPos.x < WIN_WIDTH - space.x)
            moveDir.x += _playerSpeed * DELTA_TIME;
        _player->SetLeftRight(0);
    }

    shared_ptr<RectCollider> currentGround;
    bool onGround = CheckGroundCollision(currentGround);

    if (KEY_DOWN(VK_SPACE) && onGround && !_isJumping)
    {
        _velocity.y = _jumpHeight; 
        _isJumping = true;
    }

    _velocity.y -= _gravity * DELTA_TIME;
    moveDir.y += _velocity.y * DELTA_TIME;

    if (onGround && _velocity.y <= 0.0f)
    {
        _isJumping = false;
        _velocity.y = 0.0f;

        Vector pos = _collider->GetWorldPos();
        float playerBottom = pos.y - _collider->GetWorldScale().y * 0.5f;
        float groundTop = currentGround->GetWorldPos().y + currentGround->GetWorldScale().y * 0.5f;

        if (playerBottom < groundTop)
        {
            pos.y = groundTop + _collider->GetWorldScale().y * 0.5f;
            _collider->SetPos(pos);
        }
    }

    _collider->GetTransform()->AddPos(moveDir);

    for (auto& ground : _grounds)
    {
        if (_collider->IsCollision(ground))
        {
            Vector playerPos = _collider->GetWorldPos();
            Vector groundPos = ground->GetWorldPos();
            Vector playerScale = _collider->GetWorldScale();
            Vector groundScale = ground->GetWorldScale();

            float playerBottom = playerPos.y - playerScale.y * 0.5f;
            float playerTop = playerPos.y + playerScale.y * 0.5f;
            float groundTop = groundPos.y + groundScale.y * 0.5f;
            float groundBottom = groundPos.y - groundScale.y * 0.5f;

            if (playerBottom <= groundTop && playerTop > groundTop && _velocity.y <= 0)
            {
                Vector pos = _collider->GetWorldPos();
                pos.y = groundTop + playerScale.y * 0.5f;
                _collider->SetPos(pos);
                _velocity.y = 0;
                _isJumping = false;
            }
            else if (playerTop >= groundBottom && playerBottom < groundBottom && _velocity.y > 0)
            {
                Vector pos = _collider->GetWorldPos();
                pos.y = groundBottom - playerScale.y * 0.5f;
                _collider->SetPos(pos);
                _velocity.y = 0;
            }
            else
            {
                ground->Block(_collider);
            }
        }
    }
}

void Mario::Pick()
{
    if (auto torch = _torch.lock())
    {
        bool canPick = _collider->IsCollision(torch->GetCollider());
        if (KEY_DOWN('Z') && canPick)
        {
            torch->GetTransform()->SetParent(_equipment);
            _isEquip = true;
        }
    }
}

bool Mario::CheckGroundCollision(shared_ptr<RectCollider>& hitGround)
{
    Vector playerPos = _collider->GetWorldPos();
    Vector playerScale = _collider->GetWorldScale();
    float playerBottom = playerPos.y - playerScale.y * 0.5f;

    for (auto& ground : _grounds)
    {
        Vector groundPos = ground->GetWorldPos();
        Vector groundScale = ground->GetWorldScale();
        float groundTop = groundPos.y + groundScale.y * 0.5f;

        bool xOverlap = (playerPos.x + playerScale.x * 0.5f > groundPos.x - groundScale.x * 0.5f) &&
            (playerPos.x - playerScale.x * 0.5f < groundPos.x + groundScale.x * 0.5f);

        if (xOverlap && playerBottom <= groundTop + 10.0f && _velocity.y <= 0)
        {
            hitGround = ground;
            return true;
        }
    }
    return false;
}