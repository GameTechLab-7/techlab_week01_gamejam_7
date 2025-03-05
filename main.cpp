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
#include "GameObject/CircleObject.h"
#include "GameObject/Player.h"
#include "Manager/GameManager.h"
#include "Manager/ObjectManager.h"
#include "Scene/MainGameScene.h"
#include "Math/FVector3.h"
#include "Weapon/WeaponA.h"
#include "Weapon/WeaponB.h"


enum class EPrimitiveType : UINT8
{
	EPT_Triangle,
	EPT_Cube,
	EPT_Sphere,
	EPT_Max,
};


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

    default:
        return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}

void OpenDebugConsole()
{
	AllocConsole(); // 콘솔 창 생성

	// 표준 출력 및 입력을 콘솔과 연결
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	freopen_s((FILE**)stdin, "CONIN$", "r", stdin);

	std::cout << "Debug Console Opened!" << std::endl;
}

void CloseDebugConsole()
{
	FreeConsole(); // 콘솔 창 닫기
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

	ObjectManager& objectManager = ObjectManager::GetInstance();
	objectManager.Initialize(&Renderer);
	
	Player* player = objectManager.RegistObject<Player>(EWorld::First);
	
	WeaponA* weaponA = new WeaponA(player);

	player->SetWeapon(weaponA);
	player->SetVelocity(FVector3{ 1, 0, 0 });
	// player 자체에서 바인딩?


	Player* playerB = objectManager.RegistObject<Player>(EWorld::Second);

	WeaponB* weaponB = new WeaponB(playerB);

	playerB->SetWeapon(weaponB);
	playerB->SetVelocity(FVector3{ 1, 0, 0 });

	//DirectX::
	float spawnCooldown = 1.f;
	float timer = 0.f;

	//int NumOfBalls = 1;

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
		timer += DeltaTime;

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

    	
#pragma region Test Code
    	// 게 임 로직 - Update, FixedUpdate, 플레이어 경험치, point, 
		// 웨폰 + 레벨 시스템 + 레벨 증가 등

		// 플레이어, 웨폰 클래스

		// 몬스터, 잡다한 충돌


		//std::cout << timer << '\n';
    	if (timer > spawnCooldown) {
    		timer = 0.f;
    		player->SetAngle(player->GetAngle() + 0.5f);
    		player->SetVelocity(-player->GetVelocity());

			playerB->SetAngle(playerB->GetAngle() + 0.5f);
			playerB->SetVelocity(-playerB->GetVelocity());
    		std::cout << player->GetAngle() << '\n';
    		// new랑 position, velocity, radius
    		// objectManager.RegistObject<Player>(First);
    		// objectManager.RegistObject<Player>(Second);
    	}
#pragma endregion

    	
    	// FixedTimeStep 만큼 업데이트
    	while (Accumulator >= FixedTimeStep)
    	{
			//FixedUpdate(FixedTimeStep); //마찬가지로 ObjectManager에 있는 FixedUpdate

    		// 공 충돌 처리 -> 마찬가지로 ObjectManager에서
    		//if (CircleObject::CheckCollision(*Balls[i], *Balls[j]))
    		//{
    		//	Balls[i]->HandleBallCollision(*Balls[j]);
    		//}

    		Accumulator -= FixedTimeStep;
    	}


        // 렌더링 준비 작업
        Renderer.Prepare();
        Renderer.PrepareShader();

    	GameManager::GetInstance().GetCurrentScene()->Update(DeltaTime);

        // ImGui Frame 생성
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("DX11 Property Window");
        {
            ImGui::Text("Hello, World!");
        	ImGui::Text("FPS: %.3f", ImGui::GetIO().Framerate);

			ImGui::Text("Current Scene: %s" , GameManager::GetInstance().GetCurrentScene()->GetName().c_str());
			if (ImGui::Button("Move to Main Game Scene"))
			{
				GameManager::GetInstance().ChangeScene<MainGameScene>();
				GameManager::GetInstance().GetCurrentScene()->SetName("MainGameScene");
			}
        }
        ImGui::End();

        // ImGui 렌더링
        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

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


