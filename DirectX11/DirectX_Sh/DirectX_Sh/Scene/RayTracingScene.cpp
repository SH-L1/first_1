// RayTracingScene.cpp - 수정된 버전
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

    _walls[0]->SetPos(Vector(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.1f)); // 바닥
    _walls[1]->SetPos(Vector(WIN_WIDTH * 0.2f, WIN_HEIGHT * 0.5f)); // 왼쪽 벽
    _walls[2]->SetPos(Vector(WIN_WIDTH * 0.8f, WIN_HEIGHT * 0.3f)); // 오른쪽 벽

    _player->SetPos(Vector(CENTRE.x, WIN_HEIGHT * 0.4f));
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

    // 활성화된 횃불과 플레이어 연결
    for (auto torch : _torches)
    {
        if (torch->GetActive())
        {
            _player->SetTorch(torch);
            break; // 첫 번째 활성화된 횃불만 연결
        }
    }
}

void RayTracingScene::Render()
{
    // 모든 오브젝트 데이터 수집
    vector<ObjectData> objects;

    // 벽 오브젝트 추가
    for (auto wall : _walls)
    {
        ObjectData objData;
        objData.pos = wall->GetCollider()->GetWorldPos();
        objData.size = wall->GetCollider()->GetWorldScale();
        objData.uvOffset = XMFLOAT2(0.0f, 0.0f);
        objData.uvScale = XMFLOAT2(1.0f, 1.0f);
        objData.reflectivity = 0.3f;
        objData.type = 0; // 사각형
        objData.pad0 = 0;
        objData.pad1 = 0;
        objects.push_back(objData);
    }

    // 활성화된 횃불 오브젝트 추가
    for (auto torch : _torches)
    {
        if (torch->GetActive())
        {
            objects.push_back(torch->GetObjectData());
        }
    }

    // 플레이어 오브젝트 추가
    objects.push_back(_player->GetObjectData());

    // 레이트레이싱 데이터 설정
    RayTracingBuffer::Data rayData = _player->GetLightData();
    rayData.objectCount = static_cast<int>(objects.size());

    // 플레이어의 Quad에 데이터 설정
    _player->SetLightData(rayData, static_cast<int>(objects.size()));

    // 개별 오브젝트 렌더링
    _player->Render();

    for (auto torch : _torches)
    {
        if (torch->GetActive())
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
        (*deactiveTorch)->GetTransform()->SetPos(mousePos);

        // 디버그 출력
        OutputDebugStringA("Created torch at mouse position\n");
    }
    else
    {
        OutputDebugStringA("No available torch slots\n");
    }
}