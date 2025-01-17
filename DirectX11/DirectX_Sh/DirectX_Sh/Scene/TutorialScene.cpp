#include "framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
    _vertexBuffer = make_shared<VertexBuffer>();
    _vs = make_shared<VertexShader>(L"Shaders/TutorialShader.hlsl");
    _ps = make_shared<PixelShader>(L"Shaders/TutorialShader.hlsl");

    _srv = make_shared<SRV>(L"Resource/SIUUUU.jpg");
    _samplerState = make_shared<SamplerState>();

    // TEST : °æ¼·,Áö¹Î
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
}

void TutorialScene::Render()
{
    _vs->IASetInputLayout();

    _vertexBuffer->IASet(0);

    _vs->VSSet();
    _ps->PSSet();

    _srv->PSSet_SRV(0);
    _samplerState->PSSet_Sampler(0);

    DC->Draw(6, 0);
}
