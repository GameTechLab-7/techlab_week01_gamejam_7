#include "GameManager.h"
#include <iostream>
#include "TitleScene.h"

void GameManager::Init()
{
	ChangeScene<TitleScene>();
	std::cout << "GameManager Init" << std::endl;
}
