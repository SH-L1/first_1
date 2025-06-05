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

    _velocity.y += _gravity * DELTA_TIME;
    moveDir.y -= _velocity.y * DELTA_TIME;

    // 먼저 y축만 이동
    _collider->GetTransform()->AddPos(Vector(0, moveDir.y));

    bool onGround = false;
    for (auto& ground : _grounds)
    {
        if (_collider->IsCollision(ground))
        {
            ground->Block(_collider);

            float playerBottom = _collider->GetWorldPos().y - _collider->GetWorldScale().y * 0.5f;
            float groundTop = ground->GetWorldPos().y + ground->GetWorldScale().y * 0.5f;

            if (abs(playerBottom - groundTop) < 5.0f)
            {
                onGround = true;
                _velocity.y = 0;
                _isJumping = false;
            }
        }
    }

    // 그 다음 x축 이동
    _collider->GetTransform()->AddPos(Vector(moveDir.x, 0));

    // x축 충돌 체크 (필요한 경우)
    for (auto& ground : _grounds)
    {
        if (_collider->IsCollision(ground))
        {
            // x축 충돌 시 원위치로
            _collider->GetTransform()->AddPos(Vector(-moveDir.x, 0));
            break;
        }
    }

    if (KEY_DOWN(VK_SPACE) && onGround && !_isJumping)
    {
        _velocity.y = _jumpHeight;
        _isJumping = true;
    }
}

void Mario::Pick()
{
    if (auto torch = _torch.lock())
    {
        bool canPick = _collider->IsCollision(torch->GetCollider());
        if (KEY_DOWN('Z') && canPick)
        {
            torch->GetCollider()->GetTransform()->SetParent(_equipment);
            torch->GetCollider()->SetPos(Vector(0.0f, 50.0f));
            torch->SetActive(false);
            _isEquip = true;
        }
    }
}