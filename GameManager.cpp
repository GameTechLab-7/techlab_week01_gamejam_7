#include "GameManager.h"
#include <iostream>
/// <summary>
/// ���η������� ��. ������Ʈ �ٲ�� ���� ����
/// </summary>
void GameManager::HandleState()
{
	if (PrevState == CurrentState)
		return;

	PrevState = CurrentState;

	switch (CurrentState)
	{
	case EGameState::Init:
		// !TODO : ���� ���� �� ����

		std::cout << "init" << std::endl;
		//CurrentState = EGameState::MainMenu;
		break;
	case EGameState::MainMenu:
		// !TODO : ���θ޴� state ���� �� ����
		std::cout << "MainMenu" << std::endl;

		break;
	case EGameState::MainGame:
		// !TODO : ���ΰ��� state ���� �� ����
		std::cout << "MainGame" << std::endl;

		break;
	case EGameState::Result:
		// !TODO : ���ȭ�� ���� �� ����
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
