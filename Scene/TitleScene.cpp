#include "TitleScene.h"
#include <Windows.h>
#include "Scene/PresetScene.h"
#include "Manager/GameManager.h"
#include "Manager/AudioManager.h"


void TitleScene::LoadScene()
{
	AudioManager::GetInstance().PlayLoop(AudioType::TitleBackground);
}

void TitleScene::ExitScene()
{
}

void TitleScene::Render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Title Scene");
	{
		if (ImGui::Button("Start")) 
		{
			GameManager::GetInstance().ChangeScene<PresetScene>();
			GameManager::GetInstance().GetCurrentScene()->SetName("PresetScene");
		}

		if (ImGui::Button("Quit"))
		{
			PostQuitMessage(0);
		}
	}

	ImGui::End();

	// ImGui 렌더링
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void TitleScene::OnClickQuit()
{
	PostQuitMessage(0);
}

void TitleScene::OnClickStart()
{
	GameManager::GetInstance().ChangeScene<PresetScene>();
}
