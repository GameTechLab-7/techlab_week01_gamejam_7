#include "GameManager.h"
#include "Scene/TitleScene.h"

#include <iostream>

void GameManager::Init(URenderer* renderer)
{
	if (bInitialized)
	{
		return;
	}

	ChangeScene<TitleScene>();
	CurrentScene->SetName("TitleScene");
	Renderer = renderer;

	std::cout << "GameManager Init" << std::endl;
}
