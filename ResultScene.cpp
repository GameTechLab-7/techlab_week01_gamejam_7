#include "ResultScene.h"
#include <windows.h>
#include "Scene/PresetScene.h"
#include "Manager/GameManager.h"
#include "Manager/AudioManager.h"

void ResultScene::LoadScene()
{
	AudioManager::GetInstance().PlayLoop(AudioType::EndBackground);
}

void ResultScene::ExitScene()
{
}

void ResultScene::Render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Game Over!");
	{
		ImGui::Text("Winner is %s" , GameManager::GetInstance().DeadPlayerWorld == EWorld::First ? "Player2" : "Player1");

		//if (ImGui::Button("ReStart"))
		//{
		//	GameManager::GetInstance().ChangeScene<PresetScene>();
		//	GameManager::GetInstance().GetCurrentScene()->SetName("PresetScene");
		//}

		//if (ImGui::Button("Quit"))
		//{
		//	PostQuitMessage(0);
		//}
	}

	ImGui::End();

	// ImGui 렌더링
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ResultScene::OnClickQuit()
{
	PostQuitMessage(0);
}

void ResultScene::OnClickRestart()
{
	GameManager::GetInstance().ChangeScene<PresetScene>();
}
