#pragma once

class SRV
{
public:
	SRV(wstring path);
	~SRV();

	void PSSet_SRV(int slot);

private:
	void CreateSRV(wstring path);

	ScratchImage image;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> srv;
};