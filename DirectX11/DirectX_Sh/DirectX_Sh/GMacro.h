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
