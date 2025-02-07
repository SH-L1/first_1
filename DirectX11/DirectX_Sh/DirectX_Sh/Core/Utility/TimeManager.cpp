#include "framework.h"
#include "TimeManager.h"

TimeManager* TimeManager::_instance = nullptr;

TimeManager::TimeManager()
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency); // �ʴ� CPU ���� ��
	QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime); // �ֱ� ���� ��

	_timeScale = 1.0 / (double)_periodFrequency;
}

TimeManager::~TimeManager()
{
}

void TimeManager::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);

	_deltaTime = (double)(_curTime - _lastTime) * _timeScale;

	// lockFPS : ������ ����
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

	// ���� 1�ʰ� �帧
	if (_oneSecCount > 1.0)
	{
		_oneSecCount = 0.0;
		_frameRate = _frameCount; // frameRate : 1�� �� ������Ʈ Ƚ��
		_frameCount = 0;
	}

	_runTime += _deltaTime; // ���� ����� �ð�
}	