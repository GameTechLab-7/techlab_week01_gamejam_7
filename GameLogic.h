#pragma once
#include <enum.h>
#include <unordered_map>
#include "Manager/GameManager.h"
#include "Scene/MainGameScene.h"

const int LVUP_THRESHOLD = 100;

struct PlayerState
{
	int Preset;
	int Score;
	int Exp;
	int Lv;
};

class GameLogic
{
private:
	std::unordered_map<EWorld , PlayerState> PlayerStates;

public:
	GameLogic();
	~GameLogic();

	void AddScore(EWorld World)
	{
		PlayerStates[ World ].Score++;
	}

	void AddExp(EWorld World, int exp) 
	{
		PlayerStates[ World ].Exp += exp;
		if (PlayerStates[ World ].Exp >= LVUP_THRESHOLD)
		{
			Upgrade(World);
		}
	}

	void Upgrade(EWorld World)
	{
		MainGameScene* mainScene = GameManager::GetInstance().GetCurrentScene<MainGameScene>(); 

		if (mainScene == nullptr)
			return;
		Player* player = mainScene->GetPlayer(World);

		// !TODO : 플레이어 레벨업로직
	}

	/// <summary>
	/// init은 Preset씬에서 실행
	/// </summary>
	void Init();

};

