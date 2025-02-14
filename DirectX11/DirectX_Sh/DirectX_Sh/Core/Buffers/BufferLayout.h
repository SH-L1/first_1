#pragma once

class MatrixBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		XMMATRIX matrix = XMMatrixIdentity();
	};

	MatrixBuffer() : ConstantBuffer(&_data, sizeof(Data)) {}
	~MatrixBuffer() {}

	void SetData(XMMATRIX value)
	{
		_data.matrix = XMMatrixTranspose(value);
	}

private:
	Data _data;
};

class ColorBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		XMFLOAT4 color;
	};

	ColorBuffer() : ConstantBuffer(&_data, sizeof(Data)) {}
	~ColorBuffer() {}

	void SetData(XMFLOAT4 color)
	{
		_data.color = color;
	}

private:
	Data _data;
};