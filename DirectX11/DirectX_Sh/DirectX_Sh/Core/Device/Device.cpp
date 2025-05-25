// Device.cpp - 디버깅 강화 버전
#include "framework.h"
#include "Device.h"

Device* Device::_instance = nullptr;

Device::Device()
{
    OutputDebugStringA("Device initialization started\n");

    RECT rect;
    GetClientRect(hWnd, &rect);
    UINT width = rect.right - rect.left;
    UINT height = rect.bottom - rect.top;

    char buffer[256];
    sprintf_s(buffer, "Window size: %d x %d\n", width, height);
    OutputDebugStringA(buffer);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };

    UINT featureSize = ARRAYSIZE(featureLevels);

    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;

    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = true;

    HRESULT hResult = D3D11CreateDeviceAndSwapChain
    (
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG, // 디버그 모드 유지
        featureLevels,
        featureSize,
        D3D11_SDK_VERSION,
        &sd,
        swapChain.GetAddressOf(),
        device.GetAddressOf(),
        nullptr,
        deviceContext.GetAddressOf()
    );

    if (FAILED(hResult))
    {
        OutputDebugStringA("CRITICAL ERROR: Failed to create D3D11 device and swap chain!\n");

        // 디버그 레이어 없이 다시 시도
        hResult = D3D11CreateDeviceAndSwapChain
        (
            nullptr,
            D3D_DRIVER_TYPE_HARDWARE,
            0,
            0, // 디버그 플래그 제거
            featureLevels,
            featureSize,
            D3D11_SDK_VERSION,
            &sd,
            swapChain.GetAddressOf(),
            device.GetAddressOf(),
            nullptr,
            deviceContext.GetAddressOf()
        );

        if (FAILED(hResult))
        {
            OutputDebugStringA("CRITICAL ERROR: Failed to create D3D11 device even without debug layer!\n");
            MessageBoxA(nullptr, "DirectX 11 초기화 실패", "오류", MB_OK);
            exit(-1);
        }
        else
        {
            OutputDebugStringA("Device created successfully without debug layer\n");
        }
    }
    else
    {
        OutputDebugStringA("Device and swap chain created successfully\n");
    }

    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
    hResult = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());

    if (FAILED(hResult))
    {
        OutputDebugStringA("ERROR: Failed to get back buffer\n");
    }
    else
    {
        OutputDebugStringA("Back buffer retrieved successfully\n");
    }

    hResult = device->CreateRenderTargetView(backBuffer.Get(), nullptr, renderTargetView.GetAddressOf());

    if (FAILED(hResult))
    {
        OutputDebugStringA("ERROR: Failed to create render target view\n");
    }
    else
    {
        OutputDebugStringA("Render target view created successfully\n");
    }

    deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), nullptr);

    D3D11_VIEWPORT vp;
    vp.Width = (float)width;
    vp.Height = (float)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    deviceContext->RSSetViewports(1, &vp);

    OutputDebugStringA("Viewport set successfully\n");
    OutputDebugStringA("Device initialization completed\n");
}

Device::~Device()
{
    OutputDebugStringA("Device destructor called\n");
}