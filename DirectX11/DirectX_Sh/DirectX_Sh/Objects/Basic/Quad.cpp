#include "framework.h"
#include "Quad.h"

Quad::Quad(wstring textureFile)
{
    CreateMesh();
    CreateMaterial(textureFile);
}

Quad::~Quad()
{
}

void Quad::Update()
{

}

void Quad::Render()
{
    _vs->IASetInputLayout();

    _vertexBuffer->IASet(0);

    _vs->VSSet();
    _ps->PSSet();

    _srv->PSSet_SRV(0);
    _samplerState->PSSet_Sampler(0);

    DC->Draw(6, 0);
}

void Quad::CreateMaterial(wstring textureFile)
{
    _vs = make_shared<VertexShader>(L"Shaders/TutorialShader.hlsl");
    _ps = make_shared<PixelShader>(L"Shaders/TutorialShader.hlsl");

    _srv = make_shared<SRV>(textureFile);
    _samplerState = make_shared<SamplerState>();
}

void Quad::CreateMesh()
{
    _vertices =
    {
        { XMFLOAT3(-0.5f, 0.5f, 0.0f), XMFLOAT2(0,0) },
        { XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT2(1,1) },
        { XMFLOAT3(-0.5f, -0.5f, 0.0f), XMFLOAT2(0,1) },

        { XMFLOAT3(-0.5f, 0.5f, 0.0f), XMFLOAT2(0,0) },
        { XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT2(1,0) },
        { XMFLOAT3(0.5f, -0.5f, 0.0f), XMFLOAT2(1,1) },
    };

    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex_Texture), _vertices.size(), 0);
}