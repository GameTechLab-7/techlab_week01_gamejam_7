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
}
