// SRV.cpp - 간단한 버전 (CreateDefaultTexture 함수 없이)
#include "framework.h"
#include "SRV.h"

SRV::SRV(wstring path)
{
    CreateSRV(path);
}

SRV::~SRV()
{
}

void SRV::PSSet_SRV(int slot)
{
    DC->PSSetShaderResources(slot, 1, srv.GetAddressOf());
}

Vector SRV::GetImageSize()
{
    return Vector((float)image.GetMetadata().width, (float)image.GetMetadata().height);
}

void SRV::CreateSRV(wstring path)
{
    // 디버깅을 위한 경로 출력
    std::wcout << L"Loading texture: " << path << std::endl;

    // 파일 존재 여부 확인
    DWORD fileAttributes = GetFileAttributesW(path.c_str());
    if (fileAttributes == INVALID_FILE_ATTRIBUTES)
    {
        std::wcout << L"ERROR: Texture file does not exist: " << path << std::endl;
        OutputDebugStringA("ERROR: Texture file not found!\n");
        return; // 기본 텍스처 생성 대신 그냥 리턴
    }
    else
    {
        std::wcout << L"Texture file found: " << path << std::endl;
        OutputDebugStringA("Texture file found\n");
    }

    // 텍스처 로딩
    HRESULT hr = LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, nullptr, image);

    if (FAILED(hr))
    {
        char buffer[512];
        sprintf_s(buffer, "ERROR: Failed to load texture file. HRESULT: 0x%08X\n", hr);
        OutputDebugStringA(buffer);
        std::wcout << L"Failed to load texture: " << path << std::endl;
        return;
    }

    // 이미지 정보 출력
    const auto& metadata = image.GetMetadata();
    char buffer[512];
    sprintf_s(buffer, "Texture loaded successfully: %dx%d, Format: %d\n",
        (int)metadata.width, (int)metadata.height, (int)metadata.format);
    OutputDebugStringA(buffer);
    std::wcout << L"Texture size: " << metadata.width << L"x" << metadata.height << std::endl;

    // SRV 생성
    hr = CreateShaderResourceView(DEVICE.Get(), image.GetImages(),
        image.GetImageCount(), metadata, srv.GetAddressOf());

    if (FAILED(hr))
    {
        sprintf_s(buffer, "ERROR: Failed to create SRV. HRESULT: 0x%08X\n", hr);
        OutputDebugStringA(buffer);
        return;
    }

    OutputDebugStringA("SRV created successfully\n");
}