#include "GameManager.h"
#include <iostream>


void GameManager::HandleState()
{
    if (PrevState == CurrentState) return;
    PrevState = CurrentState;

    switch (CurrentState)
    {
    case EGameState::Init:
        // !TODO : ���� ���� �� ����

        std::cout << "init" << std::endl;
        // CurrentState = EGameState::MainMenu;
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

    case EGameState::None:
        break;
    }
}

void GameManager::SetGameState(EGameState inState)
{
    CurrentState = inState;
}

EGameState GameManager::GetGameState() const
{
    return CurrentState;
}
