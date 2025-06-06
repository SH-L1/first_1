#include "framework.h"
#include "RayTracingScene.h"

RayTracingScene::RayTracingScene()
{
    _background = make_shared<Background>();
    _player = make_shared<Mario>();
    _torch = make_shared<Torch>();

    for (int i = 0; i < _wallNum; i++)
    {
        shared_ptr<Wall> wall = make_shared<Wall>();
        _walls.push_back(wall);
    }

    _walls[0]->SetPos(Vector(WIN_WIDTH * 0.5f, 80.0f));  
    _walls[1]->SetPos(Vector(WIN_WIDTH * 0.07f, WIN_HEIGHT * 0.3f)); 
    _walls[2]->SetPos(Vector(WIN_WIDTH * 0.85f, WIN_HEIGHT * 0.4f)); 

    _player->SetPos(Vector(CENTRE.x, 300.0f));
    _player->SetGround(_walls[0]->GetCollider());

    vector<shared_ptr<RectCollider>> allGrounds;
    for (auto wall : _walls)
    {
        allGrounds.push_back(wall->GetCollider());
    }

    _player->SetGrounds(allGrounds);
    _torch->SetGrounds(allGrounds);
    _player->SetTorch(_torch);
}

RayTracingScene::~RayTracingScene()
{
}

void RayTracingScene::PreUpdate()
{
    _player->PreUpdate();
    _torch->PreUpdate();

    for (auto wall : _walls)
        wall->PreUpdate();
}

void RayTracingScene::Update()
{
    _background->Update();
    _player->Update();

    if (KEY_DOWN(VK_LBUTTON))
    {
        CreateTorchOnSreen();
    }

    _torch->Update();

    for (auto wall : _walls)
        wall->Update();
}

void RayTracingScene::Render()
{
    RayTracingBuffer::Data lightData;
    lightData.material = XMFLOAT4(0.15f, 0.85f, 0.0f, 0.0f);
    lightData.screenOrigin = XMFLOAT4(WIN_WIDTH, WIN_HEIGHT, CENTRE.x, CENTRE.y);

    if (_torch->GetActive())
    {
        Vector lightPos;
        float lightIntensity = 1.2f;
        float lightRadius = 500.0f;

        if (_player->IsEquipped())
        {
            lightPos = _player->GetCollider()->GetWorldPos();
            lightPos.y += 50.0f;
        }
        else
        {
            lightPos = _torch->GetCollider()->GetWorldPos();
        }

        lightData.lightAndShadow = XMFLOAT4(
            lightPos.x,
            lightPos.y,
            lightIntensity,
            lightRadius
        );
        lightData.objectCount = 1; 
    }
    else
    {
        lightData.lightAndShadow = XMFLOAT4(0, 0, 0, 0);
        lightData.objectCount = 0;
    }

    _background->GetQuad()->SetRayTracingData(lightData);
    _background->Render();

    for (auto wall : _walls)
    {
        wall->GetQuad()->SetRayTracingData(lightData);
        wall->Render();
    }

    _player->GetQuad()->SetRayTracingData(lightData);
    _player->Render();

    if (_torch->GetActive() && !_player->IsEquipped())
    {
        RayTracingBuffer::Data torchLightData = lightData;
        torchLightData.material = XMFLOAT4(1.0f, 0.0f, 0.0f, 0.0f);
        _torch->GetQuad()->SetRayTracingData(torchLightData);
        _torch->Render();
    }
}

void RayTracingScene::PostRender()
{
    _player->GetCollider()->SetColor(GREEN);
    _player->PostRender();

    for (auto wall : _walls)
    {
        wall->GetCollider()->SetColor(RED);
        wall->PostRender();
    }

    if (_torch->GetActive())
    {
        _torch->GetCollider()->SetColor(BLUE);
        _torch->PostRender();
    }
}

void RayTracingScene::CreateTorchOnSreen()
{
    if (!_torch->GetActive())
    {
        _torch->SetActive(true);
        _torch->SetPosition(mousePos);
    }
}