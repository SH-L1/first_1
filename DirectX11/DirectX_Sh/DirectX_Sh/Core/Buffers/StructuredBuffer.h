#pragma once

template<typename T>
class StructuredBuffer
{
public:
    StructuredBuffer(UINT count = 1);
    ~StructuredBuffer();

    void CreateSRV();
    void CreateUAV();

    void SetData(const T* data, UINT count);
    void SetPS(UINT slot);
    void SetCS(UINT slot);
    void Update();

private:
    Microsoft::WRL::ComPtr<ID3D11Buffer> _buffer;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> _srv;
    Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView> _uav;

    vector<T> _data;
    UINT _count;
};

template<typename T>
StructuredBuffer<T>::StructuredBuffer(UINT count)
    : _count(count)
{
    _data.resize(count);
    CreateSRV();
}

template<typename T>
StructuredBuffer<T>::~StructuredBuffer()
{
}

template<typename T>
void StructuredBuffer<T>::CreateSRV()
{
    D3D11_BUFFER_DESC desc = {};
    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = sizeof(T) * _count;
    desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
    desc.StructureByteStride = sizeof(T);

    HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, _buffer.GetAddressOf());
    if (FAILED(hr))
        OutputDebugStringA("Failed to create StructuredBuffer\n");

    D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = DXGI_FORMAT_UNKNOWN;
    srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
    srvDesc.Buffer.ElementOffset = 0;
    srvDesc.Buffer.NumElements = _count;

    hr = DEVICE->CreateShaderResourceView(_buffer.Get(), &srvDesc, _srv.GetAddressOf());
    if (FAILED(hr))
        OutputDebugStringA("Failed to create SRV for StructuredBuffer\n");
}

template<typename T>
void StructuredBuffer<T>::CreateUAV()
{
    D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
    uavDesc.Format = DXGI_FORMAT_UNKNOWN;
    uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
    uavDesc.Buffer.FirstElement = 0;
    uavDesc.Buffer.NumElements = _count;

    HRESULT hr = DEVICE->CreateUnorderedAccessView(_buffer.Get(), &uavDesc, _uav.GetAddressOf());
    if (FAILED(hr))
        OutputDebugStringA("Failed to create UAV for StructuredBuffer\n");
}

template<typename T>
void StructuredBuffer<T>::SetData(const T* data, UINT count)
{
    _count = count;
    _data.resize(count);
    memcpy(_data.data(), data, sizeof(T) * count);
}

template<typename T>
void StructuredBuffer<T>::SetPS(UINT slot)
{
    DC->PSSetShaderResources(slot, 1, _srv.GetAddressOf());
}

template<typename T>
void StructuredBuffer<T>::SetCS(UINT slot)
{
    DC->CSSetShaderResources(slot, 1, _srv.GetAddressOf());
}

template<typename T>
void StructuredBuffer<T>::Update()
{
    DC->UpdateSubresource(_buffer.Get(), 0, nullptr, _data.data(), sizeof(T) * _count, 0);
}