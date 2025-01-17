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

    // 快府啊 弊副 葛电 巴
    _scene->Render();

    Device::Instance()->GetSwapChain()->Present(0, 0);
}
