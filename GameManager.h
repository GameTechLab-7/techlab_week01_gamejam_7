#pragma once
#include "Singleton.h"

enum class EGameState
{
	None = -1,
	Init = 0,
	MainMenu,
	MainGame,
	Result,
};

class GameManager : public Singleton<GameManager>
{


private:
	EGameState CurrentState = EGameState::Init;
	EGameState PrevState = EGameState::None;

public:
	void HandleState();
	void SetGameState(EGameState inState);
	EGameState GetGameState();

};