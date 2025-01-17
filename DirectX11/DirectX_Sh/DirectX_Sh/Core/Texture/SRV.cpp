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

void SRV::CreateSRV(wstring path)
{
	LoadFromWICFile(path.c_str(), WIC_FLAGS_NONE, nullptr, image);
	CreateShaderResourceView(DEVICE.Get(), image.GetImages(), image.GetImageCount(), image.GetMetadata(), srv.GetAddressOf());
}
