#include "framework.h"
#include "RayTracingScene.h"

RayTracingScene::RayTracingScene()
{
    _rayTracer = make_shared<RayTracingRenderer>();

    // 레이트레이싱 테스트를 위한 오브젝트 추가
    // 바닥 사각형
    _rayTracer->AddObject(
        Vector(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.1f), 
        Vector(WIN_WIDTH * 0.8f, 20.0f), 
        Vector(0.8f, 0.8f, 0.8f), 
        0.1f, 
        0 // 사각형
    );

    // 왼쪽 벽
    _rayTracer->AddObject(
        Vector(WIN_WIDTH * 0.1f, WIN_HEIGHT * 0.5f),
        Vector(20.0f, WIN_HEIGHT * 0.8f),
        Vector(0.7f, 0.3f, 0.3f),
        0.1f,
        0 // 사각형
    );

    // 오른쪽 벽
    _rayTracer->AddObject(
        Vector(WIN_WIDTH * 0.9f, WIN_HEIGHT * 0.5f),
        Vector(20.0f, WIN_HEIGHT * 0.8f),
        Vector(0.3f, 0.7f, 0.3f),
        0.1f,
        0 // 사각형
    );
    
    // 공 - 왼쪽
    _rayTracer->AddObject(
        Vector(WIN_WIDTH * 0.3f, WIN_HEIGHT * 0.5f),
        Vector(80.0f, 80.0f),
        Vector(1.0f, 0.8f, 0.3f),
        0.5f,
        1 // 원
    );

    // 공 - 오른쪽
    _rayTracer->AddObject(
        Vector(WIN_WIDTH * 0.7f, WIN_HEIGHT * 0.5f),
        Vector(100.0f, 100.0f),
        Vector(0.3f, 0.5f, 1.0f),
        0.3f,
        1 // 원
    );

    // 공 - 가운데
    _rayTracer->AddObject(
        Vector(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.4f),
        Vector(60.0f, 60.0f),
        Vector(0.8f, 0.3f, 0.8f),
        0.2f,
        1 // 원
    );
}

RayTracingScene::~RayTracingScene()
{
}

void RayTracingScene::Update()
{
    // 스페이스바로 라이트 이동 토글
    if (KEY_DOWN(VK_SPACE))
        _isLightMoving = !_isLightMoving;

    if (_isLightMoving)
    {
        // 라이트를 원형으로 이동
        _lightAngle += DELTA_TIME * 0.5f;
        float radius = WIN_WIDTH * 0.3f;
        Vector lightPos(
            WIN_WIDTH * 0.5f + cos(_lightAngle) * radius,
            WIN_HEIGHT * 0.5f + sin(_lightAngle) * radius
        );
        _rayTracer->SetLight(lightPos, 1.0f);
    }
    else
    {
        // 마우스 위치로 라이트 이동
        _rayTracer->SetLight(mousePos, 1.0f);
    }

    _rayTracer->Update();
}

void RayTracingScene::Render()
{
    _rayTracer->Render();
} 