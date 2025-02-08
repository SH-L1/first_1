#pragma once

#define DEVICE Device::Instance()->GetDevice()
#define DC Device::Instance()->GetDC()

#define WIN_WIDTH 1200
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

#define BLACK		 RGB(0,0,0)
#define WHITE		 RGB(255,255,255)
#define RED			 RGB(255,0,0)
#define GREEN		 RGB(0,255,0)