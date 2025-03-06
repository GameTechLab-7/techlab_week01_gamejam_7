#pragma comment(lib, "user32")
#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

#include <Windows.h>
#include <iostream>
#include <string>

#include "ImGui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui_impl_dx11.h"

#include "URenderer.h"
#include "InputSystem.h"
#include "GameObject/CircleObject.h"
#include "GameObject/Player.h"
#include "Manager/UIManager.h"
#include "Manager/GameManager.h"
#include "Manager/ObjectManager.h"
#include "Scene/MainGameScene.h"
#include "Scene/TitleScene.h"
#include "Scene/PresetScene.h"
#include "Math/FVector3.h"

#include "Weapon/WeaponA.h"
#include "Weapon/WeaponB.h"


// ImGui WndProc 정의
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// 각종 윈도우 관련 메시지(이벤트)를 처리하는 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    // ImGui의 메시지를 처리
    if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
    {
        return true;
    }

    switch (uMsg)
    {
    // 창이 제거될 때 (창 닫기, Alt+F4 등)
    case WM_DESTROY:
        PostQuitMessage(0); // 프로그램 종료
        break;
	case WM_KEYDOWN:
		InputSystem::GetInstance().KeyDown(static_cast<EKeyCode>(wParam));
		break;
	case WM_KEYUP:
		InputSystem::GetInstance().KeyUp(static_cast<EKeyCode>( wParam ));
		break;
    case WM_LBUTTONDOWN:
        POINTS DownPts = MAKEPOINTS(lParam);
        RECT dRect;
        int dWidth , dHeight;
        if (GetClientRect(hWnd , &dRect)) {
            dWidth = dRect.right - dRect.left;
            dHeight = dRect.bottom - dRect.top;
        }
        InputSystem::GetInstance().MouseKeyDown(FVector3(DownPts.x , DownPts.y , 0), FVector3(dWidth , dHeight , 0));
        std::cout << "MouseDown " << InputSystem::GetInstance().GetMouseDownRatioPos().x << " " << InputSystem::GetInstance().GetMouseDownRatioPos().y << "\n";
        break;
    case WM_LBUTTONUP:
        POINTS UpPts = MAKEPOINTS(lParam);
        RECT uRect;
        int uWidth , uHeight;
        if (GetClientRect(hWnd , &uRect)) {
            uWidth = uRect.right - uRect.left;
            uHeight = uRect.bottom - uRect.top;
        }
        InputSystem::GetInstance().MouseKeyUp(FVector3(UpPts.x , UpPts.y , 0), FVector3(uWidth , uHeight , 0));
        //std::cout << "MouseUp" << InputSystem::GetInstance().GetMouseUpRatioPos().x << " " << InputSystem::GetInstance().GetMouseUpRatioPos().y << "\n";
        break;
    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}

void OpenDebugConsole()
{
#ifdef _DEBUG
	AllocConsole(); // 콘솔 창 생성

	// 표준 출력 및 입력을 콘솔과 연결
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);

	std::cout << "Debug Console Opened!" << std::endl;
#endif // _DEBUG
}

void CloseDebugConsole()
{
#ifdef _DEBUG
	FreeConsole(); // 콘솔 창 닫기
#endif // _DEBUG
}


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nShowCmd)
{
#pragma region Init Window
    // 사용 안하는 파라미터들
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nShowCmd);

    // 윈도우 클래스 이름 및 타이틀 이름
    constexpr WCHAR WndClassName[] = L"DX11 Test Window Class";
    constexpr WCHAR WndTitle[] = L"DX11 Test Window";

    // 윈도우 클래스 등록
    WNDCLASS WndClass = {0, WndProc, 0, 0, hInstance, nullptr, nullptr, nullptr, nullptr, WndClassName};
    RegisterClass(&WndClass);

    // 1024 x 1024로 윈도우 생성
    const HWND hWnd = CreateWindowEx(
        0, WndClassName, WndTitle,
        WS_POPUP | WS_VISIBLE | WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        1024, 1024,
        nullptr, nullptr, hInstance, nullptr
    );

	OpenDebugConsole();
#pragma endregion Init Window
	
#pragma region Init Renderer & ImGui
    // 렌더러 초기화
    URenderer Renderer;
    Renderer.Create(hWnd);
    Renderer.CreateShader();
    Renderer.CreateConstantBuffer();

    // ImGui 초기화
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    // ImGui Backend 초기화
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplDX11_Init(Renderer.GetDevice(), Renderer.GetDeviceContext());
#pragma endregion Init Renderer & ImGui

    // FPS 제한
    constexpr int TargetFPS = 60;
    constexpr double TargetDeltaTime = 1000.0f / TargetFPS; // 1 FPS의 목표 시간 (ms)

    // 고성능 타이머 초기화
    LARGE_INTEGER Frequency;
    QueryPerformanceFrequency(&Frequency);

    LARGE_INTEGER StartTime;
    QueryPerformanceCounter(&StartTime);

    float Accumulator = 0.0; // Fixed Update에 사용되는 값
    constexpr float FixedTimeStep = 1.0f / TargetFPS;

	GameManager::GetInstance().Init(&Renderer);

    UIManager& uiManager = UIManager::GetInstance();
    uiManager.Initialize(&Renderer);

    UIObject* ui = UIManager::GetInstance().RegistUIObject<UIObject>(EScene::Title);
    ui->SetLocation(FVector3(0.0f , 0.5f , 0.0f));
    ui->SetScale(FVector3(1.0f , 0.5f , 0.2f)); //왜 y,z가 x,y인지???
    ui->SetOnClickEvent([ ] () {std::cout << "click\n"; });

	ObjectManager& objectManager = ObjectManager::GetInstance();
	objectManager.Initialize(&Renderer);
    // Main Loop
    bool bIsExit = false;
    while (bIsExit == false)
    {
        // DeltaTime 계산 (초 단위)
        const LARGE_INTEGER EndTime = StartTime;
        QueryPerformanceCounter(&StartTime);

        const float DeltaTime =
            static_cast<float>(StartTime.QuadPart - EndTime.QuadPart) / static_cast<float>(Frequency.QuadPart);

        // 누적 시간 추가
        Accumulator += DeltaTime;

        InputSystem::GetInstance().ExpireOnceMouse();

        // 메시지(이벤트) 처리
        MSG msg;
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            // 키 입력 메시지를 번역
            TranslateMessage(&msg);

            // 메시지를 등록한 Proc에 전달
            DispatchMessage(&msg);

            if (msg.message == WM_QUIT)
            {
                bIsExit = true;
                break;
            }
        }

    	// FixedTimeStep 만큼 업데이트
    	while (Accumulator >= FixedTimeStep)
    	{
    		Accumulator -= FixedTimeStep;
    	}


        // 렌더링 준비 작업
        Renderer.Prepare();
        Renderer.PrepareShader();

    	GameManager::GetInstance().GetCurrentScene()->Update(DeltaTime);
		GameManager::GetInstance().GetCurrentScene()->Render();
        UIManager::GetInstance().Update(DeltaTime);

        // 현재 화면에 보여지는 버퍼와 그리기 작업을 위한 버퍼를 서로 교환
        Renderer.SwapBuffer();


        // FPS 제한
        double ElapsedTime;
        do
        {
            Sleep(0);

            LARGE_INTEGER CurrentTime;
            QueryPerformanceCounter(&CurrentTime);

            ElapsedTime = static_cast<double>(CurrentTime.QuadPart - StartTime.QuadPart) * 1000.0 / static_cast<double>(Frequency.QuadPart);
        } while (ElapsedTime < TargetDeltaTime);
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    Renderer.ReleaseConstantBuffer();
    Renderer.ReleaseShader();
    Renderer.Release();

	CloseDebugConsole();
    return 0;
}


