#pragma once

#define PI 3.141592f

#define DEVICE Device::Instance()->GetDevice()
#define DC Device::Instance()->GetDC()

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define CENTRE Vector(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f)

#define SAMPLER StateManager::Instance()->GetSampler()
#define BLEND StateManager::Instance()->GetBlend()
#define ALPHA StateManager::Instance()->GetAlpha()
#define ADDITIVE StateManager::Instance()->GetAdditive()

#define KEY_DOWN(k) InputManager::Instance()->Down(k)
#define KEY_UP(k) InputManager::Instance()->Up(k)
#define KEY_PRESS(k) InputManager::Instance()->Press(k)

#define DELTA_TIME TimeManager::Instance()->DeltaTime()
#define RUN_TIME TimeManager::Instance()->RunTime()

#define LERP(start, end, ratio)  start + (end - start) * ratio

#define RED	{1.0f,0.0f,0.0f,1.0f}
#define GREEN {0.0f,1.0f,0.0f,1.0f}
#define BLUE {0.0f,0.0f,1.0f,1.0f}
#define WHITE {1.0f,1.0f,1.0f,1.0f}
#define BLACK {0.0f,0.0f,0.0f,1.0f}
#define GREY {0.5f,0.5f,0.5f,1.0f}