// PixelShader.cpp - ����� ��ȭ ����
#include "framework.h"
#include "PixelShader.h"

PixelShader::PixelShader(wstring file)
{
    CreatePixelBlob(file);
    CreatePixelShader();
}

PixelShader::~PixelShader()
{
}

void PixelShader::PSSet()
{
    DC->PSSetShader(pixelShader.Get(), nullptr, 0);
}

void PixelShader::CreatePixelBlob(wstring file)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    // ���� �޽����� ���� ���� �߰�
    Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

    HRESULT hr = D3DCompileFromFile(
        file.c_str(),
        nullptr,
        nullptr,
        "PS",
        "ps_5_0",
        flags,
        0,
        pixelBlob.GetAddressOf(),
        errorBlob.GetAddressOf()  // ���� ��� �߰�
    );

    // ������ ���н� ���� �޽��� ���
    if (FAILED(hr))
    {
        if (errorBlob)
        {
            char* errorMsg = (char*)errorBlob->GetBufferPointer();
            OutputDebugStringA("Pixel Shader Compile Error: ");
            OutputDebugStringA(errorMsg);
            OutputDebugStringA("\n");

            // �ֿܼ��� ���
            std::wcout << L"Failed to compile pixel shader: " << file << std::endl;
            std::cout << "Error: " << errorMsg << std::endl;
        }
        else
        {
            std::wcout << L"Failed to compile pixel shader: " << file << L" (no error message)" << std::endl;
        }

        // ���� �߻��� ���α׷� �ߴ�
        assert(false && "Pixel Shader compilation failed!");
    }
    else
    {
        // ������ �޽���
        std::wcout << L"Successfully compiled pixel shader: " << file << std::endl;
    }
}

void PixelShader::CreatePixelShader()
{
    HRESULT hr = DEVICE->CreatePixelShader(pixelBlob->GetBufferPointer(),
        pixelBlob->GetBufferSize(), nullptr, pixelShader.GetAddressOf());

    if (FAILED(hr))
    {
        OutputDebugStringA("Failed to create pixel shader\n");
        assert(false && "Pixel shader creation failed!");
    }
    else
    {
        OutputDebugStringA("Successfully created pixel shader\n");
    }
}