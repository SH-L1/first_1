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

class LeftRightBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		int leftRight = 0;
		int padding[3];
	};

	LeftRightBuffer() : ConstantBuffer(&_data, sizeof(Data)) {}
	~LeftRightBuffer() {}

	void SetData(int leftRight)
	{
		_data.leftRight = leftRight;
	}

private:
	Data _data;
};

class RayTracingBuffer : public ConstantBuffer
{
public:
	struct Data
	{
		XMFLOAT4 screenOrigin;
		XMFLOAT4 lightAndShadow;
		XMFLOAT4 material;
		int objectCount;
		int padding[3];
	};

	RayTracingBuffer() : ConstantBuffer(&_data, sizeof(Data)) {}
	~RayTracingBuffer() {}

	void SetData(const Data& data)
	{
		_data = data;
		Update();
	}

	void SetScreenOrigin(float screenW, float screenH, float originX, float originY)
	{
		_data.screenOrigin = { screenW, screenH, originX, originY };
	}

	void SetLight(float lightPosX, float lightPosY, float lightInt, float shadowInt)
	{
		_data.lightAndShadow = { lightPosX, lightPosY, lightInt, shadowInt };
	}

	void SetMaterial(float ambient, float diffuse, float specular, float shininess)
	{
		_data.material = { ambient, diffuse, specular, shininess };
	}

	void SetObjectCount(int count)
	{
		_data.objectCount = count;
	}

private:
	Data _data;
};