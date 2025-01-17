#include "framework.h"
#include "SamplerState.h"

SamplerState::SamplerState()
{
	CreateSamplerState();
}

SamplerState::~SamplerState()
{
}

void SamplerState::PSSet_Sampler(int slot)
{
    DC->PSSetSamplers(slot, 1, samplerState.GetAddressOf());
}

void SamplerState::CreateSamplerState()
{
    D3D11_SAMPLER_DESC sampDesc = {};
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

    DEVICE->CreateSamplerState(&sampDesc, samplerState.GetAddressOf());
}
