// DirectX_Sh.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "DirectX_Sh.h"

#define MAX_LOADSTRING 100

// 해상도 만큼의 픽셀을 그리는 것
// 1 pixel : RGB(255, 255, 255)
// WIN_API : Window에서 제공하는 창을 가지고 무엇을 할 수 있는가
// =>
// CPU vs GPU
// - CPU : 교수님
//  => 직렬처리에 특화
//  => 복잡한 논리연산 특화
// 
// - GPU : 학생 1만명
//  => 병렬처리에 특화
//  => 단순하고 반복되는 작업 특화
// 
// DirectX : Direct Access
// => GPU에게 일을 직접 부탁한다
// => 게임엔진을 만드는 것이 목표

// 영화촬영
// 총감독 / Programmer
// 영화사 / Engine(Unity, Unreal)
// 카메라 / View
// 세트장 / World
// 소품 / Actor
// 배우 / Actor(Pawn, Character)
// 조명 / Light

// DX
// Device => 인력사무소장
// 외주를 맡기고, 실질적인 공사 대표
// 컴퓨터의 하드웨어 기능을 점검하고, 리소스를 할당, 하드웨어에 접근할 수 있도록 도와줌
Microsoft::WRL::ComPtr<ID3D11Device> device; // Com 객체 => Create Release

// Device Context : DC => 연출감독
// 세트장을 실질적으로 꾸며주는 연출가
// 랜더링 대상을 결정(어디에 그릴지 결정)
// => 리소스(texture)를 '그래픽 파이프라인'에 바인딩하고, GPU가 수행할 명령을 지시함
Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;

// 백버퍼
// SwapChain
// DX의 인터페이스로써 1개 이사으이 표면을 포함할 수 있는 것
// => 각각의 표면(버퍼, 텍스처)을 출력하기 전에 데이터를 보관하는 용도
Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;

// 후면 버퍼를 가리키는 포인터
// 후면 버퍼(지금 당장 그릴 곳)
Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;

// 랜더링 파이프라인 단계
// 1. VertexBuffer
Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;
// 2. InputLayout
Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
// 3. VertexShader
Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
// 4. PixelShader
Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;

struct Vertex
{
    XMFLOAT3 pos;
};

void InitDevice();
void Render();

HWND hWnd;

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DIRECTXSH, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DIRECTXSH));

    InitDevice();

    MSG msg = {};

    while (msg.message != WM_QUIT)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            // 메인루프
            Render();
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DIRECTXSH));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DIRECTXSH);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void InitDevice()
{
    RECT rect;
    GetClientRect(hWnd, &rect);
    UINT width = rect.right - rect.left;
    UINT height = rect.bottom - rect.top;

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0
    };

    UINT featureSize = ARRAYSIZE(featureLevels);

    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferCount = 1;
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    // Numerator / Denominator = 화면 프레임 갱신 최고 속도

    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = true; // 창모드
    
    // 여기까지 설명서

    auto hResult = D3D11CreateDeviceAndSwapChain
    (
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        0,
        D3D11_CREATE_DEVICE_DEBUG,
        featureLevels,
        featureSize,
        D3D11_SDK_VERSION,
        &sd,
        IN swapChain.GetAddressOf(),
        IN device.GetAddressOf(),
        nullptr,
        IN deviceContext.GetAddressOf()
    );

    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
    
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
    device->CreateRenderTargetView(backBuffer.Get(), nullptr, renderTargetView.GetAddressOf());

    deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), nullptr);

    D3D11_VIEWPORT vp;
    vp.Width = width;
    vp.Height = height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    deviceContext->RSSetViewports(1, &vp);

    // Vertex Shader에 들어갈 때, 데이터(Vertex, 색.. 등등)들의 설명서
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        {
            "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
            D3D11_INPUT_PER_VERTEX_DATA, 0
        }
    };

    UINT layoutSize = ARRAYSIZE(layout);

    DWORD flags = D3DCOMPILE_ENABLE_STRICTNESS | D3DCOMPILE_DEBUG;

    Microsoft::WRL::ComPtr<ID3DBlob> vertexBlob; // VertexShader를 만들 때 필요한 것
    D3DCompileFromFile(L"Shaders/TutorialShader.hlsl", nullptr, nullptr, "VS", "vs_5_0", flags, 0, vertexBlob.GetAddressOf(), nullptr);
    
    device->CreateInputLayout(layout, layoutSize, vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), inputLayout.GetAddressOf());
    device->CreateVertexShader(vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), nullptr, IN vertexShader.GetAddressOf());

    Microsoft::WRL::ComPtr<ID3DBlob> pixelBlob; // PixelShader를 만들 때 필요한 것
    D3DCompileFromFile(L"Shaders/TutorialShader.hlsl", nullptr, nullptr, "PS", "ps_5_0", flags, 0, pixelBlob.GetAddressOf(), nullptr);

    device->CreatePixelShader(pixelBlob->GetBufferPointer(), pixelBlob->GetBufferSize(), nullptr, IN pixelShader.GetAddressOf());

    Vertex vertices[] =
    {
        // {0, 0} 위치가 창의 중심
        XMFLOAT3(-0.3f, 0.5f, 0.0f), // 좌측 상단
        XMFLOAT3(0.3f, -0.5f, 0.0f), // 우측 하단
        XMFLOAT3(-0.3f, -0.5f, 0.0f), // 좌측 하단

        XMFLOAT3(-0.3f, 0.5f, 0.0f), // 좌측 상단
        XMFLOAT3(0.3f, 0.5f, 0.0f), // 우측 상단
        XMFLOAT3(0.3f, -0.5f, 0.0f) // 우측 하단
    };

    D3D11_BUFFER_DESC bd = {};
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.ByteWidth = sizeof(Vertex) * 6;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData = {};
    initData.pSysMem = &vertices[0];

    device->CreateBuffer(&bd, &initData, vertexBuffer.GetAddressOf());
}

void Render()
{
    FLOAT myColorR = 1.0f;
    FLOAT myColorG = 1.0f;
    FLOAT myColorB = 1.0f;

    FLOAT clearColor[4] = { myColorR, myColorG, myColorB, 1.0f };

    deviceContext->ClearRenderTargetView(renderTargetView.Get(), clearColor);

    UINT stride = sizeof(Vertex); // Vertex 3 -> 12바이트
    UINT offset = 0;

    // 입력 어셈블러(Input Assembler)
    deviceContext->IASetInputLayout(inputLayout.Get());

    deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    deviceContext->VSSetShader(vertexShader.Get(), nullptr, 0);
    deviceContext->PSSetShader(pixelShader.Get(), nullptr, 0);

    deviceContext->Draw(6, 0);

    swapChain->Present(0, 0);
}