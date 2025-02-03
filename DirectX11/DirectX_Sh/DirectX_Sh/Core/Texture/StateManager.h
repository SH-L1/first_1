#pragma once

class StateManager
{
public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new StateManager;
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static StateManager* Instance() { return _instance; }

	shared_ptr<SamplerState> GetSampler() { return _sampler; }
	shared_ptr<BlendState> GetBlend() { return _blendState; }
	shared_ptr<BlendState> GetAlpha() { return _alphaState; }
	shared_ptr<BlendState> GetAdditive() { return _additiveState; }

private:
	StateManager();
	~StateManager();

	static StateManager* _instance;

	shared_ptr<SamplerState> _sampler;
	shared_ptr<BlendState> _blendState;
	shared_ptr<BlendState> _alphaState;
	shared_ptr<BlendState> _additiveState;
};