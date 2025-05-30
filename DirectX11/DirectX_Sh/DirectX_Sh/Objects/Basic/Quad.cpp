#include "framework.h"
#include "Quad.h"

Quad::Quad(wstring textureFile)
{
    CreateMaterial(textureFile);
    CreateMesh();

    _transform = make_shared<Transform>();
    _leftRightBuffer = make_shared<LeftRightBuffer>();
    _colorBuffer = make_shared<ColorBuffer>();
    _rayBuffer = make_shared<RayTracingBuffer>();
    _objects = make_shared<StructuredBuffer<ObjectData>>(100);

    SetLeftRight(0);
    AddColor(XMFLOAT4(0, 0, 0, 0));
}

Quad::~Quad()
{
}

void Quad::Update()
{
    _transform->Update();
}

void Quad::Render()
{
    _transform->Update();
    _leftRightBuffer->Update();
    _colorBuffer->Update();
    _rayBuffer->Update();
    _objects->Update();

    _vs->IASetInputLayout();
    _vertexBuffer->IASet(0);
    _indexBuffer->IASetIndexBuffer();

    _vs->VSSet();
    _ps->PSSet();

    _transform->SetVS(0);
    _leftRightBuffer->SetPS(0);
    _objects->SetPS(1);
    _colorBuffer->SetPS(2);
    _rayBuffer->SetPS(3);

    _srv->PSSet_SRV(0);
    SAMPLER->PSSet_Sampler(0);

    DC->DrawIndexed(_indices.size(), 0, 0);
}

void Quad::CreateMaterial(wstring textureFile)
{
    _vs = make_shared<VertexShader>(L"Shaders/TextureVertexShader.hlsl");
    _ps = make_shared<PixelShader>(L"Shaders/RayTracingPixelShader.hlsl");
    _srv = make_shared<SRV>(textureFile);
}

void Quad::CreateMesh()
{
    _vertices =
    {
        { XMFLOAT3(-1.0f, 1.0f, 0.0f), XMFLOAT2(0, 0) },
        { XMFLOAT3(1.0f, 1.0f, 0.0f), XMFLOAT2(1, 0) },
        { XMFLOAT3(1.0f, -1.0f, 0.0f), XMFLOAT2(1, 1) },
        { XMFLOAT3(-1.0f, -1.0f, 0.0f), XMFLOAT2(0, 1) },
    };

    _indices = { 0, 1, 2, 0, 2, 3 };

    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex_Texture), _vertices.size(), 0);
    _indexBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());
}