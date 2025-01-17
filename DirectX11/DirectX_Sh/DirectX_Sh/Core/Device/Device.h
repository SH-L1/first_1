#pragma once
class Device
{
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new Device();
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static Device* Instance()
	{
		return _instance;
	}

	Microsoft::WRL::ComPtr<ID3D11Device> GetDevice() { return device; }
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> GetDC() { return deviceContext; }
	Microsoft::WRL::ComPtr<IDXGISwapChain> GetSwapChain() { return swapChain; }
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRTV() { return renderTargetView; }

private:
	Device();
	~Device();

	static Device* _instance;

	Microsoft::WRL::ComPtr<ID3D11Device>					device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>				deviceContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain>					swapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>			renderTargetView;
};

