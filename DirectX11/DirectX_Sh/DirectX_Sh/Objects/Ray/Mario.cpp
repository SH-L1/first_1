#include "framework.h"
#include "Mario.h"

Mario::Mario()
{
    vector<wstring> texturePaths = {
        L"Resource/Mario_Big_Idle.png",
        L"Resource/Mario/Mario_Big_Idle.png",
        L"Resource/mario.png",
        L"Textures/Mario_Big_Idle.png",
        L"Assets/Mario_Big_Idle.png",
        L"../Resource/Mario_Big_Idle.png",
        L"./Resource/Mario_Big_Idle.png"
    };

    wstring selectedPath = L"Resource/Mario_Big_Idle.png"; // 기본값
    bool foundTexture = false;

    for (const auto& path : texturePaths)
    {
        DWORD fileAttributes = GetFileAttributesW(path.c_str());
        if (fileAttributes != INVALID_FILE_ATTRIBUTES)
        {
            selectedPath = path;
            foundTexture = true;
            std::wcout << L"Found texture at: " << path << std::endl;
            OutputDebugStringA("Texture file found!\n");
            break;
        }
        else
        {
            std::wcout << L"Not found: " << path << std::endl;
        }
    }

    if (!foundTexture)
    {
        OutputDebugStringA("WARNING: No texture file found, using default path\n");
        std::wcout << L"No texture found, using: " << selectedPath << std::endl;
    }

    _player = make_shared<Quad>(selectedPath);
    _collider = make_shared<RectCollider>(_player->GetImageSize());
    _equipment = make_shared<Transform>();

    _collider->SetPos(CENTRE);
    _collider->Update();

    _player->GetTransform()->SetParent(_collider->GetTransform());

    // 마리오 크기 키우기 (3배 확대)
    _player->GetTransform()->SetScale(Vector(3.0f, 3.0f));
    _collider->GetTransform()->SetScale(Vector(3.0f, 3.0f));

    _equipment->SetParent(_collider->GetTransform());
    _equipment->SetPos(Vector(0.0f, 1.0f));

    _rayData.screenOrigin = XMFLOAT4(WIN_WIDTH, WIN_HEIGHT, CENTRE.x, CENTRE.y);
    _rayData.lightAndShadow = XMFLOAT4(100.0f, 100.0f, 1.0f, 0.5f);
    _rayData.material = XMFLOAT4(0.4f, 0.8f, 1.0f, 32.0f);
    _rayData.objectCount = 1;

    _objData.pos = _collider->GetWorldPos();
    _objData.size = _player->GetImageSize() * 3.0f;
    _objData.uvOffset = XMFLOAT2(0.0f, 0.0f);
    _objData.uvScale = XMFLOAT2(1.0f, 1.0f);
    _objData.reflectivity = 0.5f;
    _objData.type = 0;
    _objData.pad0 = 0;
    _objData.pad1 = 0;

    _player->AddColor(XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f));
    _player->SetLeftRight(0);

    _player->Update();

    OutputDebugStringA("Mario created with texture path check\n");
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

	if (auto ground = _ground.lock())
	{
		bool onGround = _collider->IsCollision(ground);
		if (KEY_DOWN(VK_SPACE) && onGround && !_isJumping)
		{
			_velocity.y = _jumpHeight;
			_isJumping = true;
		}

		if (onGround && _velocity.y >= 0.0f)
		{
			_isJumping = false;
			_velocity.y = 0.0f;
		}
	}

	_velocity.y += _gravity * DELTA_TIME;
	moveDir.y += _velocity.y * DELTA_TIME;

	_collider->GetTransform()->AddPos(moveDir);
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