#include <iostream>
#include "Manager/GameManager.h"
#include "Scene/TitleScene.h"

void GameManager::Init()
{
	ChangeScene<TitleScene>();
	std::cout << "GameManager Init" << std::endl;
}
