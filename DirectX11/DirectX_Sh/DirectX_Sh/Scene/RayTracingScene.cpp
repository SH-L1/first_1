#include "framework.h"
#include "RayTracingScene.h"

RayTracingScene::RayTracingScene()
{
    _player = make_shared<Mario>();

    for (int i = 0; i < _torchNum; i++)
    {
        shared_ptr<Torch> torch = make_shared<Torch>();
        _torches.push_back(torch);
    }

    for (int i = 0; i < _wallNum; i++)
    {
        shared_ptr<Wall> wall = make_shared<Wall>();
        _walls.push_back(wall);
    }

    _walls[0]->SetPos(Vector(WIN_WIDTH * 0.5f, 50.0f));
    _walls[1]->SetPos(Vector(WIN_WIDTH * 0.2f, WIN_HEIGHT * 0.3f));
    _walls[2]->SetPos(Vector(WIN_WIDTH * 0.8f, WIN_HEIGHT * 0.6f));

    _player->SetPos(Vector(CENTRE.x, 200.0f));
    _player->SetGround(_walls[0]->GetCollider());

    for (auto torch : _torches)
    {
        torch->SetGround(_walls[0]->GetCollider());
    }
}

RayTracingScene::~RayTracingScene()
{
}

void RayTracingScene::PreUpdate()
{
    for (auto torch : _torches)
        torch->PreUpdate();

    _player->PreUpdate();

    for (auto wall : _walls)
        wall->PreUpdate();
}

void RayTracingScene::Update()
{
    if (KEY_DOWN(VK_LBUTTON))
    {
        CreateTorchOnSreen();
    }

    for (auto torch : _torches)
        torch->Update();

    _player->Update();

    for (auto wall : _walls)
        wall->Update();

    for (auto torch : _torches)
    {
        if (torch->GetActive())
            _player->SetTorch(torch);
    }
}

void RayTracingScene::Render()
{
    vector<ObjectData> objects;

    for (auto wall : _walls)
    {
        ObjectData objData;
        objData.pos = wall->GetCollider()->GetWorldPos();
        objData.size = wall->GetCollider()->GetWorldScale();
        objData.uvOffset = XMFLOAT2(0.0f, 0.0f);
        objData.uvScale = XMFLOAT2(1.0f, 1.0f);
        objData.reflectivity = 0.5f;
        objData.type = 0;
        objData.pad0 = 0;
        objData.pad1 = 0;
        objects.push_back(objData);
    }

    vector<shared_ptr<Torch>> activeTorches;
    for (auto torch : _torches)
    {
        if (torch->GetActive())
        {
            objects.push_back(torch->GetObjectData());
            activeTorches.push_back(torch);
        }
    }

    objects.push_back(_player->GetObjectData());

    RayTracingBuffer::Data rayData;

    if (!activeTorches.empty())
    {
        rayData = activeTorches[0]->GetLightData();
    }
    else
    {
        rayData = _player->GetLightData();
        rayData.lightAndShadow = XMFLOAT4(CENTRE.x, WIN_HEIGHT * 0.8f, 2.0f, 0.7f);
    }

    rayData.objectCount = static_cast<int>(objects.size());

    for (auto wall : _walls)
    {
        wall->GetQuad()->SetRayTracingData(rayData);
        wall->GetQuad()->SetObjectData(objects.data(), objects.size());
    }

    for (auto torch : activeTorches)
    {
        torch->SetRayTracingData(rayData);
        torch->SetObjectData(objects.data(), objects.size());
    }

    _player->SetLightData(rayData, static_cast<int>(objects.size()));
    _player->GetQuad()->SetRayTracingData(rayData);
    _player->GetQuad()->SetObjectData(objects.data(), objects.size());

    _player->Render();

    for (auto torch : activeTorches)
    {
        torch->Render();
    }

    for (auto wall : _walls)
    {
        wall->Render();
    }
}

void RayTracingScene::PostRender()
{
    for (auto wall : _walls)
        wall->PostRender();

    for (auto torch : _torches)
        torch->PostRender();

    _player->PostRender();
}

void RayTracingScene::CreateTorchOnSreen()
{
    auto deactiveTorch = find_if(_torches.begin(), _torches.end(), [](const auto& torch) -> bool {
        return !torch->GetActive();
        });

    if (deactiveTorch != _torches.end())
    {
        (*deactiveTorch)->SetActive(true);
        (*deactiveTorch)->SetPosition(mousePos);
    }
}