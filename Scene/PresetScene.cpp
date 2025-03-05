#include "PresetScene.h"
#include "Manager/GameManager.h"


void PresetScene::LoadScene()
{
	GameManager::GetInstance().InitGameLogic();
}

void PresetScene::ExitScene()
{
}

void PresetScene::Render()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::Begin("Preset Scene");
	{
		if (ImGui::BeginCombo("Player1 Preset" , std::to_string(Player1Preset).c_str()))
		{
			for (int i = 0; i < 2; i++)
			{
				bool isSelected = ( Player1Preset == i );
				if (ImGui::Selectable(std::to_string(i).c_str() , isSelected))
				{
					Player1Preset = i;
				}
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		if (ImGui::BeginCombo("Player2 Preset" , std::to_string(Player2Preset).c_str()))
		{
			for (int i = 0; i < 2; i++)
			{
				bool isSelected = ( Player2Preset == i );
				if (ImGui::Selectable(std::to_string(i).c_str() , isSelected))
				{
					Player2Preset = i;
				}
				if (isSelected)
				{
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}

		if (ImGui::Button("Start"))
		{
			GameManager::GetInstance().GetLogic()->SetPreset(First , Player1Preset);
			GameManager::GetInstance().GetLogic()->SetPreset(Second , Player2Preset);

			GameManager::GetInstance().ChangeScene<MainGameScene>();
			GameManager::GetInstance().GetCurrentScene()->SetName("MainGameScene");
		}
	}
	ImGui::End();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
