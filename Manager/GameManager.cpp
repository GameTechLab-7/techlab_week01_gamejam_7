#include "GameManager.h"
#include "Scene/TitleScene.h"

#include <iostream>

void GameManager::Init(URenderer* InRenderer)
{
	if (bInitialized)
	{
		return;
	}

	ChangeScene<TitleScene>();
	CurrentScene->SetName("TitleScene");
	Renderer = InRenderer;

	std::cout << "GameManager Init" << std::endl;
}

void GameManager::InitGameLogic()
{
	if (Logic)
	{
		return;
	}

	Logic = std::make_unique<GameLogic>();
	Logic->Init();
}
