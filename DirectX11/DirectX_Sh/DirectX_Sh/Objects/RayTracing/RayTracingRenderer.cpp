#include "framework.h"
#include "RayTracingRenderer.h"

RayTracingRenderer::RayTracingRenderer()
{
    CreateMesh();
    CreateShaders();

    _transform = make_shared<Transform>();
    _rayTracingBuffer = make_shared<RayTracingBuffer>();
    _rtObjectBuffer = make_shared<RTObjectBuffer>();

    // 초기 설정
    _rayTracingBuffer->SetData(Vector(WIN_WIDTH, WIN_HEIGHT), Vector(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f));
    _rayTracingBuffer->SetLight(Vector(WIN_WIDTH * 0.3f, WIN_HEIGHT * 0.7f), 1.0f);
    _rayTracingBuffer->SetShadow(0.5f, 0.2f);
    _rayTracingBuffer->SetMaterial(0.8f, 0.5f, 20.0f);
    _rayTracingBuffer->SetObjectCount(0);
    _rayTracingBuffer->Update();
}

RayTracingRenderer::~RayTracingRenderer()
{
}

void RayTracingRenderer::Update()
{
    _transform->Update();
    _rayTracingBuffer->Update();
    _rtObjectBuffer->Update();
}

void RayTracingRenderer::Render()
{
    _vs->IASetInputLayout();

    _vertexBuffer->IASet(0);
    _indexBuffer->IASetIndexBuffer();

    _vs->VSSet();
    _ps->PSSet();

    _transform->SetVS(0);
    _rayTracingBuffer->SetPS(0);
    _rtObjectBuffer->SetPS(1);

    SAMPLER->PSSet_Sampler(0);

    DC->DrawIndexed(_indices.size(), 0, 0);
}

void RayTracingRenderer::AddObject(Vector pos, Vector size, Vector color, float reflectivity, int type)
{
    if (_objectCount >= 16) 
        return; // 최대 16개 오브젝트 제한

    _rtObjectBuffer->SetObjectData(_objectCount, pos, size, color, reflectivity, type);
    _objectCount++;
    
    _rayTracingBuffer->SetObjectCount(_objectCount);
    _rtObjectBuffer->Update();
    _rayTracingBuffer->Update();
}

void RayTracingRenderer::SetLight(Vector pos, float intensity)
{
    _rayTracingBuffer->SetLight(pos, intensity);
    _rayTracingBuffer->Update();
}

void RayTracingRenderer::SetShadow(float shadowIntensity, float ambient)
{
    _rayTracingBuffer->SetShadow(shadowIntensity, ambient);
    _rayTracingBuffer->Update();
}

void RayTracingRenderer::SetMaterial(float diffuse, float specular, float shininess)
{
    _rayTracingBuffer->SetMaterial(diffuse, specular, shininess);
    _rayTracingBuffer->Update();
}

void RayTracingRenderer::CreateMesh()
{
    // 전체 화면을 덮는 사각형 생성
    _vertices =
    {
        { XMFLOAT3(0.0f, WIN_HEIGHT, 0.0f), XMFLOAT2(0, 0) },
        { XMFLOAT3(WIN_WIDTH, WIN_HEIGHT, 0.0f), XMFLOAT2(1, 0) },
        { XMFLOAT3(WIN_WIDTH, 0.0f, 0.0f), XMFLOAT2(1, 1) },
        { XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0, 1) }
    };

    _indices =
    {
        0, 1, 2,
        0, 2, 3
    };

    _vertexBuffer = make_shared<VertexBuffer>(_vertices.data(), sizeof(Vertex_Texture), _vertices.size(), 0);
    _indexBuffer = make_shared<IndexBuffer>(_indices.data(), _indices.size());
}

void RayTracingRenderer::CreateShaders()
{
    _vs = make_shared<VertexShader>(L"Shaders/RayTracingVertexShader.hlsl");
    _ps = make_shared<PixelShader>(L"Shaders/RayTracingPixelShader.hlsl");
} 