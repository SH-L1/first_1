#pragma once

class TimeManager
{
private:
	TimeManager();
	~TimeManager();

public:
	static void Create()
	{
		if (_instance == nullptr)
			_instance = new TimeManager;
	}

	static void Delete()
	{
		if (_instance != nullptr)
			delete _instance;
	}

	static TimeManager* GetInstance()
	{
		if (_instance != nullptr)
			return _instance;
	}

	void Update();

	double DeltaTime() { return _deltaTime; }
	double RunTime() { return _runTime; }
	void SetLockFps(double fps) { _lockFPS = fps; }
	void SetTimeScale(float timeScale) { _timeScale = timeScale; }
	void SetTimeScaleOrigin() { _timeScale = 1.0 / (double)_periodFrequency; }

private:
	static TimeManager* _instance;

	double _timeScale = 0.0;
	double _deltaTime = 0.0f; // �ð���ȭ�� => �ѹ� ������Ʈ�� �ɸ��� �ð�
	
	unsigned __int64 _curTime = 0;
	unsigned __int64 _lastTime = 0;
	unsigned __int64 _periodFrequency = 0; // ���� �ֱ��� ��

	unsigned int _frameRate = 0;
	unsigned int _frameCount = 0;

	double _oneSecCount = 0;
	double _runTime = 0;
	double _lockFPS = 0;
};