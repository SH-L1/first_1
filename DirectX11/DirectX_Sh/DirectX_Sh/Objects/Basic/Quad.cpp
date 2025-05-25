// Quad.cpp - 디버깅 강화 버전
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

    // 디버그 출력
    OutputDebugStringA("Quad created successfully\n");
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
    // 디버그 출력 추가
    static int renderCount = 0;
    if (renderCount % 60 == 0) // 1초마다 한 번씩 출력
    {
        OutputDebugStringA("Quad::Render() called\n");
    }
    renderCount++;

    // 모든 업데이트 확인
    _transform->Update();
    _leftRightBuffer->Update();
    _colorBuffer->Update();
    _rayBuffer->Update();
    _objects->Update();

    // 입력 레이아웃 설정 확인
    if (_vs)
    {
        _vs->IASetInputLayout();
        OutputDebugStringA("Input layout set\n");
    }
    else
    {
        OutputDebugStringA("ERROR: Vertex shader is null!\n");
        return;
    }

    // 버퍼 설정 확인
    if (_vertexBuffer)
    {
        _vertexBuffer->IASet(0);
        OutputDebugStringA("Vertex buffer set\n");
    }
    else
    {
        OutputDebugStringA("ERROR: Vertex buffer is null!\n");
        return;
    }

    if (_indexBuffer)
    {
        _indexBuffer->IASetIndexBuffer();
        OutputDebugStringA("Index buffer set\n");
    }
    else
    {
        OutputDebugStringA("ERROR: Index buffer is null!\n");
        return;
    }

    // 셰이더 설정 확인
    if (_vs && _ps)
    {
        _vs->VSSet();
        _ps->PSSet();
        OutputDebugStringA("Shaders set\n");
    }
    else
    {
        OutputDebugStringA("ERROR: Shaders are null!\n");
        return;
    }

    // 상수 버퍼 설정
    _transform->SetVS(0);
    _leftRightBuffer->SetPS(0);
    _objects->SetPS(1);
    _colorBuffer->SetPS(2);
    _rayBuffer->SetPS(3);

    // 텍스처 및 샘플러 설정 확인
    if (_srv)
    {
        _srv->PSSet_SRV(0);
        OutputDebugStringA("Texture set\n");
    }
    else
    {
        OutputDebugStringA("ERROR: SRV is null!\n");
    }

    if (SAMPLER)
    {
        SAMPLER->PSSet_Sampler(0);
        OutputDebugStringA("Sampler set\n");
    }
    else
    {
        OutputDebugStringA("ERROR: Sampler is null!\n");
    }

    // 드로우 콜 전 최종 확인
    OutputDebugStringA("About to call DrawIndexed\n");

    // 실제 드로우 콜
    DC->DrawIndexed(_indices.size(), 0, 0);

    OutputDebugStringA("DrawIndexed completed\n");
}

void Quad::CreateMaterial(wstring textureFile)
{
    try
    {
        _vs = make_shared<VertexShader>(L"Shaders/TextureVertexShader.hlsl");
        OutputDebugStringA("Vertex shader created\n");

        _ps = make_shared<PixelShader>(L"Shaders/RayTracingPixelShader.hlsl");
        OutputDebugStringA("Pixel shader created\n");

        _srv = make_shared<SRV>(textureFile);
        OutputDebugStringA("SRV created\n");
    }
    catch (...)
    {
        OutputDebugStringA("ERROR: Exception in CreateMaterial\n");
    }
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

    try
    {
        _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex_Texture), _vertices.size(), 0);
        OutputDebugStringA("Vertex buffer created\n");

        _indexBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());
        OutputDebugStringA("Index buffer created\n");
    }
    catch (...)
    {
        OutputDebugStringA("ERROR: Exception in CreateMesh\n");
    }
}