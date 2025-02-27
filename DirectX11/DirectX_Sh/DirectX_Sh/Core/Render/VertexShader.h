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

	Microsoft::WRL::ComPtr<ID3DBlob> _vertexBlob;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> _inputLayOut;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> _vertexShader;
	Microsoft::WRL::ComPtr<ID3D11ShaderReflection> _reflection;
};