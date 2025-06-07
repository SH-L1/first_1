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

    _player->SetLeftRight(0);

    _player->Update();
}

Mario::~Mario()
{
}

void Mario::PreUpdate()
{
    _collider->Update();
}

void Mario::Update()
{
    Input();
    _objData.pos = _collider->GetWorldPos();

    _equipment->Update();
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
    Vector curPos = _collider->GetWorldPos();
    Vector space = _collider->GetWorldScale() * 0.5f;

    if (KEY_PRESS('A'))
    {
        curPos.x -= _playerSpeed * DELTA_TIME;
        _player->SetLeftRight(1);
    }
    if (KEY_PRESS('D'))
    {
        curPos.x += _playerSpeed * DELTA_TIME;
        _player->SetLeftRight(0);
    }

    bool onGround = false;
    float groundY = -9999.0f;
    float floatHeight = 3.0f;

    for (auto& ground : _grounds)
    {
        float playerBottom = curPos.y - _collider->GetWorldScale().y * 0.5f;
        float playerLeft = curPos.x - _collider->GetWorldScale().x * 0.5f;
        float playerRight = curPos.x + _collider->GetWorldScale().x * 0.5f;

        float groundTop = ground->GetWorldPos().y + ground->GetWorldScale().y * 0.5f;
        float groundLeft = ground->GetWorldPos().x - ground->GetWorldScale().x * 0.5f;
        float groundRight = ground->GetWorldPos().x + ground->GetWorldScale().x * 0.5f;

        if (playerRight > groundLeft && playerLeft < groundRight)
        {
            float expectedBottom = groundTop + floatHeight;
            float tolerance = 2.0f;

            if (abs(playerBottom - expectedBottom) <= tolerance)
            {
                onGround = true;
                groundY = groundTop;
                break;
            }
            else if (playerBottom < expectedBottom + 20.0f && playerBottom > expectedBottom && _velocity.y > 0)
            {
                if (groundTop > groundY)
                {
                    groundY = groundTop;
                }
            }
        }
    }

    if (KEY_DOWN(VK_SPACE))
    {
        if (onGround && !_isJumping)
        {
            _velocity.y = -_jumpHeight;
            _isJumping = true;
            onGround = false;
        }
    }

    if (!onGround)
    {
        _velocity.y += _gravity * DELTA_TIME;
        curPos.y -= _velocity.y * DELTA_TIME;
    }
    else
    {
        if (_velocity.y > 0)
        {
            _velocity.y = 0;
            _isJumping = false;
        }
        curPos.y = groundY + _collider->GetWorldScale().y * 0.5f + floatHeight;
    }

    _collider->SetPos(curPos);
    _collider->GetTransform()->Update();

    if (!onGround && _velocity.y > 0)
    {
        for (auto& ground : _grounds)
        {
            if (_collider->IsCollision(ground))
            {
                float playerBottom = _collider->GetWorldPos().y - _collider->GetWorldScale().y * 0.5f;
                float groundTop = ground->GetWorldPos().y + ground->GetWorldScale().y * 0.5f;

                _velocity.y = 0;
                _isJumping = false;
                curPos.y = groundTop + _collider->GetWorldScale().y * 0.5f + floatHeight;
                _collider->SetPos(curPos);
                _collider->GetTransform()->Update();
                break;
            }
        }
    }

    Vector finalPos = _collider->GetWorldPos();
    if (finalPos.x < space.x) finalPos.x = space.x;
    if (finalPos.x > WIN_WIDTH - space.x) finalPos.x = WIN_WIDTH - space.x;
    if (finalPos.y < space.y)
    {
        finalPos.y = space.y;
        _velocity.y = 0;
    }

    _collider->SetPos(finalPos);
    _collider->GetTransform()->Update();
}

void Mario::Pick()
{
    if (auto torch = _torch.lock())
    {
        if (!torch->IsPickedUp() && torch->GetActive())
        {
            bool canPick = _collider->IsCollision(torch->GetCollider());
            if (KEY_DOWN('Z') && canPick)
            {
                torch->GetCollider()->GetTransform()->SetParent(_equipment);
                torch->GetCollider()->GetTransform()->SetPos(Vector(0.0f, 20.0f));

                Vector marioScale = _collider->GetTransform()->GetWorldScale();
                Vector torchOriginalScale = torch->GetCollider()->GetTransform()->GetScale();
                Vector compensatedScale = Vector(
                    torchOriginalScale.x / marioScale.x,
                    torchOriginalScale.y / marioScale.y
                );
                torch->GetCollider()->GetTransform()->SetScale(compensatedScale);

                torch->SetPickedUp(true);
                _isEquip = true;
            }
        }
    }
}