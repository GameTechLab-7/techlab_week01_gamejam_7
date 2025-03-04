#include "GameManager.h"
#include "Scene/TitleScene.h"

#include <iostream>

void GameManager::Init()
{
	ChangeScene<TitleScene>();
	std::cout << "GameManager Init" << std::endl;
}
