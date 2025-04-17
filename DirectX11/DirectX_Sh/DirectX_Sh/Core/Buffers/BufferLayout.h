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
		Vector screenSize = { 0.0f, 0.0f };
		Vector origin = { 0.0f, 0.0f };
		
		// 광원 정보
		Vector lightPos = { 0.0f, 0.0f };
		float lightIntensity = 1.0f;
		
		// 그림자 설정
		float shadowIntensity = 0.5f;
		float ambient = 0.2f;
		
		// 재질 특성
		float diffuse = 0.8f;
		float specular = 0.5f;
		float shininess = 20.0f;
		
		int objectCount = 0;
		int padding = 0;
	};

	RayTracingBuffer() : ConstantBuffer(&_data, sizeof(Data)) {}
	~RayTracingBuffer() {}

	void SetData(Vector screenSize, Vector origin)
	{
		_data.screenSize = screenSize;
		_data.origin = origin;
	}

	void SetLight(Vector pos, float intensity)
	{
		_data.lightPos = pos;
		_data.lightIntensity = intensity;
	}

	void SetShadow(float shadowIntensity, float ambient)
	{
		_data.shadowIntensity = shadowIntensity;
		_data.ambient = ambient;
	}

	void SetMaterial(float diffuse, float specular, float shininess)
	{
		_data.diffuse = diffuse;
		_data.specular = specular;
		_data.shininess = shininess;
	}

	void SetObjectCount(int count)
	{
		_data.objectCount = count;
	}

private:
	Data _data;
};

// 2D 레이트레이싱용 오브젝트 정보 버퍼
class RTObjectBuffer : public ConstantBuffer
{
public:
	struct ObjectData
	{
		Vector pos = { 0.0f, 0.0f };
		Vector size = { 0.0f, 0.0f };
		Vector color = { 1.0f, 1.0f, 1.0f };
		float reflectivity = 0.0f;
		int type = 0; // 0: 사각형, 1: 원
		int padding[3] = { 0 };
	};

	struct Data
	{
		ObjectData objects[16]; // 최대 16개 오브젝트 지원
	};

	RTObjectBuffer() : ConstantBuffer(&_data, sizeof(Data)) {}
	~RTObjectBuffer() {}

	void SetObjectData(int index, Vector pos, Vector size, Vector color, float reflectivity, int type)
	{
		if (index >= 16) return;
		
		_data.objects[index].pos = pos;
		_data.objects[index].size = size;
		_data.objects[index].color = color;
		_data.objects[index].reflectivity = reflectivity;
		_data.objects[index].type = type;
	}

private:
	Data _data;
};