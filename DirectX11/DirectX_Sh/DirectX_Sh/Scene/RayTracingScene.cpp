// RayTracingScene.cpp - ������ ����
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

    _walls[0]->SetPos(Vector(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.1f)); // �ٴ�
    _walls[1]->SetPos(Vector(WIN_WIDTH * 0.2f, WIN_HEIGHT * 0.5f)); // ���� ��
    _walls[2]->SetPos(Vector(WIN_WIDTH * 0.8f, WIN_HEIGHT * 0.3f)); // ������ ��

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

    // Ȱ��ȭ�� ȶ�Ұ� �÷��̾� ����
    for (auto torch : _torches)
    {
        if (torch->GetActive())
        {
            _player->SetTorch(torch);
            break; // ù ��° Ȱ��ȭ�� ȶ�Ҹ� ����
        }
    }
}

void RayTracingScene::Render()
{
    // ��� ������Ʈ ������ ����
    vector<ObjectData> objects;

    // �� ������Ʈ �߰�
    for (auto wall : _walls)
    {
        ObjectData objData;
        objData.pos = wall->GetCollider()->GetWorldPos();
        objData.size = wall->GetCollider()->GetWorldScale();
        objData.uvOffset = XMFLOAT2(0.0f, 0.0f);
        objData.uvScale = XMFLOAT2(1.0f, 1.0f);
        objData.reflectivity = 0.3f;
        objData.type = 0; // �簢��
        objData.pad0 = 0;
        objData.pad1 = 0;
        objects.push_back(objData);
    }

    // Ȱ��ȭ�� ȶ�� ������Ʈ �߰�
    for (auto torch : _torches)
    {
        if (torch->GetActive())
        {
            objects.push_back(torch->GetObjectData());
        }
    }

    // �÷��̾� ������Ʈ �߰�
    objects.push_back(_player->GetObjectData());

    // ����Ʈ���̽� ������ ����
    RayTracingBuffer::Data rayData = _player->GetLightData();
    rayData.objectCount = static_cast<int>(objects.size());

    // �÷��̾��� Quad�� ������ ����
    _player->SetLightData(rayData, static_cast<int>(objects.size()));

    // ���� ������Ʈ ������
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

        // ����� ���
        OutputDebugStringA("Created torch at mouse position\n");
    }
    else
    {
        OutputDebugStringA("No available torch slots\n");
    }
}