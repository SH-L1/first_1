#pragma once

#define PI 3.141592f

#define DEVICE Device::GetInstance()->GetDevice()
#define DC Device::GetInstance()->GetDC()

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define CENTRE Vector(WIN_WIDTH * 0.5f, WIN_HEIGHT * 0.5f)

#define SAMPLER StateManager::GetInstance()->GetSampler()
#define BLEND StateManager::GetInstance()->GetBlend()
#define ALPHA StateManager::GetInstance()->GetAlpha()
#define ADDITIVE StateManager::GetInstance()->GetAdditive()

#define KEY_DOWN(k) InputManager::GetInstance()->Down(k)
#define KEY_UP(k) InputManager::GetInstance()->Up(k)
#define KEY_PRESS(k) InputManager::GetInstance()->Press(k)

#define DELTA_TIME TimeManager::GetInstance()->DeltaTime()
#define RUN_TIME TimeManager::GetInstance()->RunTime()

#define LERP(start, end, ratio)  start + (end - start) * ratio

#define RED	{1.0f,0.0f,0.0f,1.0f}
#define GREEN {0.0f,1.0f,0.0f,1.0f}
#define BLUE {0.0f,0.0f,1.0f,1.0f}
#define WHITE {1.0f,1.0f,1.0f,1.0f}
#define BLACK {0.0f,0.0f,0.0f,1.0f}
#define GREY {0.5f,0.5f,0.5f,1.0f}