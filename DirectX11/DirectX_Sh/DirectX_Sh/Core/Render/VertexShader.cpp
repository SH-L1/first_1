// VertexShader.cpp - 디버깅 강화 버전
#include "framework.h"
#include "VertexShader.h"

VertexShader::VertexShader(wstring file)
{
    CreateBlob(file);
    CreateInputLayOut();
    CreateVertexShader();
}

VertexShader::~VertexShader()
{
}

void VertexShader::IASetInputLayout()
{
    DC->IASetInputLayout(_inputLayOut.Get());
}

void VertexShader::VSSet()
{
    DC->VSSetShader(_vertexShader.Get(), nullptr, 0);
}

void VertexShader::CreateBlob(wstring file)
{
    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    // 에러 메시지를 위한 변수 추가
    Microsoft::WRL::ComPtr<ID3DBlob> errorBlob;

    HRESULT hr = D3DCompileFromFile(
        file.c_str(),
        nullptr,
        nullptr,
        "VS",
        "vs_5_0",
        flags,
        0,
        _vertexBlob.GetAddressOf(),
        errorBlob.GetAddressOf()  // 에러 블롭 추가
    );

    // 컴파일 실패시 에러 메시지 출력
    if (FAILED(hr))
    {
        if (errorBlob)
        {
            char* errorMsg = (char*)errorBlob->GetBufferPointer();
            OutputDebugStringA("Vertex Shader Compile Error: ");
            OutputDebugStringA(errorMsg);
            OutputDebugStringA("\n");

            // 콘솔에도 출력
            std::wcout << L"Failed to compile vertex shader: " << file << std::endl;
            std::cout << "Error: " << errorMsg << std::endl;
        }
        else
        {
            std::wcout << L"Failed to compile vertex shader: " << file << L" (no error message)" << std::endl;
        }

        // 에러 발생시 프로그램 중단
        assert(false && "Vertex Shader compilation failed!");
    }
    else
    {
        // 성공시 메시지
        std::wcout << L"Successfully compiled vertex shader: " << file << std::endl;
    }
}

void VertexShader::CreateInputLayOut()
{
    HRESULT hr = D3DReflect(_vertexBlob->GetBufferPointer(), _vertexBlob->GetBufferSize(),
        IID_ID3D11ShaderReflection, (void**)_reflection.GetAddressOf());

    if (FAILED(hr))
    {
        OutputDebugStringA("Failed to create shader reflection\n");
        assert(false && "Shader reflection failed!");
        return;
    }

    D3D11_SHADER_DESC shaderDesc;
    _reflection->GetDesc(&shaderDesc);

    vector< D3D11_INPUT_ELEMENT_DESC> inputLayouts;

    for (UINT i = 0; i < shaderDesc.InputParameters; i++)
    {
        D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
        _reflection->GetInputParameterDesc(i, &paramDesc);

        D3D11_INPUT_ELEMENT_DESC elementDesc;
        elementDesc.SemanticName = paramDesc.SemanticName;
        elementDesc.SemanticIndex = paramDesc.SemanticIndex;
        elementDesc.InputSlot = 0;
        elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
        elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
        elementDesc.InstanceDataStepRate = 0;

        if (paramDesc.Mask == 1)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
        }
        else if (paramDesc.Mask < 4)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
        }
        else if (paramDesc.Mask < 8)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
        }
        else if (paramDesc.Mask < 16)
        {
            if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
            else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
                elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
        }

        string temp = paramDesc.SemanticName;
        if (temp == "POSITION")
            elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;

        int n = temp.find_first_of('_');
        temp = temp.substr(0, n);

        if (temp == "INSTANCE")
        {
            elementDesc.InputSlot = 1;
            elementDesc.InputSlotClass = D3D11_INPUT_PER_INSTANCE_DATA;
            elementDesc.InstanceDataStepRate = 1;
        }

        inputLayouts.emplace_back(elementDesc);
    }

    hr = DEVICE->CreateInputLayout(inputLayouts.data(), inputLayouts.size(),
        _vertexBlob->GetBufferPointer(), _vertexBlob->GetBufferSize(),
        _inputLayOut.GetAddressOf());

    if (FAILED(hr))
    {
        OutputDebugStringA("Failed to create input layout\n");
        assert(false && "Input layout creation failed!");
    }
    else
    {
        OutputDebugStringA("Successfully created input layout\n");
    }
}

void VertexShader::CreateVertexShader()
{
    HRESULT hr = DEVICE->CreateVertexShader(_vertexBlob->GetBufferPointer(),
        _vertexBlob->GetBufferSize(), nullptr, _vertexShader.GetAddressOf());

    if (FAILED(hr))
    {
        OutputDebugStringA("Failed to create vertex shader\n");
        assert(false && "Vertex shader creation failed!");
    }
    else
    {
        OutputDebugStringA("Successfully created vertex shader\n");
    }
}