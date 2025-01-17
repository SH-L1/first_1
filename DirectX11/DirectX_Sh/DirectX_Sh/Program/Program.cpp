#include "framework.h"
#include "Program.h"

#include "Scene/TutorialScene.h"

Program::Program()
{
    _scene = make_shared<TutorialScene>();
}

Program::~Program()
{
}

void Program::Update()
{
    _scene->Update();
}

void Program::Render()
{
    FLOAT myColorR = 0.0f;
    FLOAT myColorG = 0.0f;
    FLOAT myColorB = 0.0f;

    FLOAT clearColor[4] = { myColorR, myColorG, myColorB, 1.0f };

    DC->ClearRenderTargetView(Device::Instance()->GetRTV().Get(), clearColor);

    
    DC->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // 우리가 그릴 모든 것
    _scene->Render();

    Device::Instance()->GetSwapChain()->Present(0, 0);
}
