#pragma once
class SamplerState
{
public:
	SamplerState();
	~SamplerState();

	void PSSet_Sampler(int slot);
private:
	void CreateSamplerState();

	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState;
};

