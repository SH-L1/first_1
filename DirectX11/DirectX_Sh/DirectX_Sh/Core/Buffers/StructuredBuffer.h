#pragma once

template<typename T>
class StructuredBuffer
{
public:
    StructuredBuffer(UINT count = 1)
    {
        D3D11_BUFFER_DESC desc = {};
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.ByteWidth = sizeof(T) * count;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
        desc.StructureByteStride = sizeof(T);

        HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, _buffer.GetAddressOf());
        assert(SUCCEEDED(hr));

        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
        srvDesc.Format = DXGI_FORMAT_UNKNOWN;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
        srvDesc.Buffer.FirstElement = 0;
        srvDesc.Buffer.NumElements = count;

        hr = DEVICE->CreateShaderResourceView(_buffer.Get(), &srvDesc, _srv.GetAddressOf());
        assert(SUCCEEDED(hr));
    }

    void SetData(const T* data, UINT count)
    {
        DC->UpdateSubresource(_buffer.Get(), 0, nullptr, data, sizeof(T) * count, 0);
    }

    void Update()
    {
    }

    void SetPS(UINT slot)
    {
        DC->PSSetShaderResources(slot, 1, _srv.GetAddressOf());
    }

private:
    ComPtr<ID3D11Buffer> _buffer;
    ComPtr<ID3D11ShaderResourceView> _srv;
};