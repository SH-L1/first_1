#pragma once
class VertexShader
{
public:
	VertexShader(wstring file);
	~VertexShader();

	void IASetInputLayout();

	void VSSet();

private:
	void CreateBlob(wstring file);
	void CreateInputLayOut();
	void CreateVertexShader();

	Microsoft::WRL::ComPtr<ID3DBlob> vertexBlob;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayOut;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
};

