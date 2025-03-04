#include "GameManager.h"
#include <iostream>
/// <summary>
/// 메인루프에서 콜. 스테이트 바뀌면 로직 실행
/// </summary>
void GameManager::HandleState()
{
	if (PrevState == CurrentState)
		return;

	PrevState = CurrentState;

	switch (CurrentState)
	{
	case EGameState::Init:
		// !TODO : 게임 시작 시 로직

		std::cout << "init" << std::endl;
		//CurrentState = EGameState::MainMenu;
		break;
	case EGameState::MainMenu:
		// !TODO : 메인메뉴 state 진입 시 로직
		std::cout << "MainMenu" << std::endl;

		break;
	case EGameState::MainGame:
		// !TODO : 메인게임 state 진입 시 로직
		std::cout << "MainGame" << std::endl;

		break;
	case EGameState::Result:
		// !TODO : 결과화면 진입 시 로직
		std::cout << "Result" << std::endl;

		break;
	}

}

void GameManager::SetGameState(EGameState inState)
{
	CurrentState = inState;
}

EGameState GameManager::GetGameState()
{
	return CurrentState;
}
