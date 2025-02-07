#include "framework.h"
#include "TimeManager.h"

TimeManager* TimeManager::_instance = nullptr;

TimeManager::TimeManager()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency); // 초당 CPU 진동 수
	QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime); // 최근 진동 수

	_timeScale = 1.0 / (double)_periodFrequency;
}

TimeManager::~TimeManager()
{
}

void TimeManager::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);

	_deltaTime = (double)(_curTime - _lastTime) * _timeScale;

	// lockFPS : 프레임 고정
	if (_lockFPS != 0)
	{
		while (_deltaTime < (1.0 / _lockFPS))
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
			_deltaTime = (double)(_curTime - _lastTime) * _timeScale;
		}
	}

	_lastTime = _curTime;

	_frameCount++;
	_oneSecCount += _deltaTime;

	// 실제 1초가 흐름
	if (_oneSecCount > 1.0)
	{
		_oneSecCount = 0.0;
		_frameRate = _frameCount; // frameRate : 1초 당 업데이트 횟수
		_frameCount = 0;
	}

	_runTime += _deltaTime; // 실제 진행된 시간
}	