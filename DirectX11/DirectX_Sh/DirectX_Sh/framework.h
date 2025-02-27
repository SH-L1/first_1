#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <memory>
#include <random>
#include <wrl/client.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "../DirectTex/DirectXTex.h"

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

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
using namespace Microsoft;

// MACRO
#include "GMacro.h"

// CORE
#include "Core/Device/Device.h"

// MATH
#include "Core/Math/Vector.h"
#include "Core/Math/Transform.h"
#include "Core/Math/Random.h"

// RENDER
#include "Core/Render/VertexLayout.h"
#include "Core/Render/VertexBuffer.h"
#include "Core/Render/IndexBuffer.h"
#include "Core/Render/VertexShader.h"
#include "Core/Render/PixelShader.h"

// TEXTURE
#include "Core/Texture/SRV.h"
#include "Core/Texture/SamplerState.h"
#include "Core/Texture/BlendState.h"
#include "Core/Texture/StateManager.h"

// BUFFER
#include "Core/Buffers/ConstantBuffer.h"
#include "Core/Buffers/BufferLayout.h"

// UTILITY
#include "Core/Utility/InputManager.h"
#include "Core/Utility/TimeManager.h"

// COLLIDER
#include "Core/Collider/Collider.h"
#include "Core/Collider/RectCollider.h"
#include "Core/Collider/CircleCollider.h"

// OBJECTS
#include "Objects/Basic/Quad.h"

// SCENE
#include "Scene/Scene.h"

// PROGRAM
#include "Program/Program.h"

extern HWND hWnd;
extern Vector mousePos;