#include "framework.h"
#include "Program.h"

#include "Scene/TutorialScene.h"
#include "Scene/DungreedScene.h"
#include "Scene/RayTracingScene.h"

Program::Program()
{
    _scene = make_shared<RayTracingScene>();

    _view = make_shared<MatrixBuffer>();
    _projection = make_shared<MatrixBuffer>();

    XMMATRIX viewM = XMMatrixIdentity();
    XMMATRIX projectionM = XMMatrixOrthographicOffCenterLH(0, WIN_WIDTH, 0, WIN_HEIGHT, 0, 1.0f);

    _view->SetData(viewM);
    _projection->SetData(projectionM);

    _view->Update();
    _projection->Update();

    TimeManager::GetInstance()->SetLockFps(60);
}

Program::~Program()
{
}

void Program::Update()
{
    InputManager::GetInstance()->Update();
    TimeManager::GetInstance()->Update();

    _scene->PreUpdate();
    _scene->Update();
}

void Program::Render()
{
    FLOAT myColorR = 1.0f;
    FLOAT myColorG = 1.0f;
    FLOAT myColorB = 1.0f;

    FLOAT clearColor[4] = { myColorR, myColorG, myColorB, 1.0f };

    DC->ClearRenderTargetView(Device::GetInstance()->GetRTV().Get(), clearColor);

    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    ALPHA->SetState();

    _view->SetVS(1);
    _projection->SetVS(2);

    _scene->Render();
    _scene->PostRender();

    Device::GetInstance()->GetSwapChain()->Present(0, 0);
}