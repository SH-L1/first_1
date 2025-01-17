// header.h: 표준 시스템 포함 파일
// 또는 프로젝트 특정 포함 파일이 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <memory>
#include <wrl/client.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "../DirectTex/DirectXTex.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

// 프로젝트 참조
// 프로젝트에 있는 코드를 제일 간단하게 갖고올 수 있는 방법

// 정적 라이브러리
// - (쓰고싶은 프로젝트).lib 빌드 파일을 만들어줌
// - #pragma comment(lib,"d3d11.lib") 이런식으로 갖고와서 계속 쓸 수 있다.

// 동적 라이브러리
// - 정적라이브러리로 만들 경우 해당 프로젝트에서 함수를 수정하고, 다시 빌드까지 해야됌.
//  ==> .dll 

using namespace std;
using namespace DirectX;

// CORE
#include "Core/Device/Device.h"

// RENDER
#include "Core/Render/VertexLayout.h"
#include "Core/Render/VertexBuffer.h"
#include "Core/Render/VertexShader.h"
#include "Core/Render/PixelShader.h"

// TEXTURE
#include "Core/Texture/SRV.h"
#include "Core/Texture/SamplerState.h"

// SCENE
#include "Scene/Scene.h"

// PROGRAM
#include "Program/Program.h"


// MACRO
#define DEVICE	Device::Instance()->GetDevice()
#define DC		Device::Instance()->GetDC()

extern HWND hWnd;
