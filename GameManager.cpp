#include "GameManager.h"
#include <iostream>
#include "TitleScene.h"

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
