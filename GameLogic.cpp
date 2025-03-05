#include "GameLogic.h"
#include "Manager/GameManager.h"
#include "Scene/TitleScene.h"

GameLogic::GameLogic()
{
}

GameLogic::~GameLogic()
{
}

void GameLogic::Init()
{
	PlayerStates[ First ] = { 0 , 0 , 0 , 1, 5, true };
	PlayerStates[ Second ] = { 0 , 0 , 0 , 1, 5, true };
}

int GameLogic::GetPreset(EWorld World)
{
	return PlayerStates[ World ].Preset;
}

int GameLogic::GetLv(EWorld World)
{
	return PlayerStates[ World ].Lv;
}


int GameLogic::GetScore(EWorld World)
{
	return PlayerStates[ World ].Score;
}

void GameLogic::AddScore(EWorld World , int Score)
{
	PlayerStates[ World ].Score += Score;
}

void GameLogic::AddExp(EWorld World , int exp)
{
	PlayerStates[ World ].Exp += exp;
	if (PlayerStates[ World ].Exp >= LVUP_THRESHOLD)
	{
		PlayerStates[ World ].Lv += 1;
		PlayerStates[ World ].Exp -= LVUP_THRESHOLD;
		SetLevel(World, PlayerStates[ World ].Lv);
	}
}

void GameLogic::SetLevel(EWorld World, int lv)
{
	MainGameScene* mainScene = GameManager::GetInstance().GetCurrentScene<MainGameScene>();

	if (mainScene == nullptr)
		return;
	Player* player = mainScene->GetPlayer(World);

	if (player != nullptr)
	{
		player->SetLevel(lv);
	}
}

void GameLogic::SpawnMonsterToWorld(EWorld World, int NumOfMonster = 1)
{
	MainGameScene* mainScene = GameManager::GetInstance().GetCurrentScene<MainGameScene>();
	if (mainScene == nullptr)
		return;
	MonsterSpawner* spawner = mainScene->GetSpawner();
	if (spawner != nullptr)
	{
		spawner->SpawnToWorld(World, NumOfMonster);
	}
}

void GameLogic::EndGame(EWorld DeadPlayerWorld)
{
	GameManager::GetInstance().ChangeScene<TitleScene>();
}

void GameLogic::OnPlayerHit(EWorld World, int Damage)
{
	PlayerStates[World].Hp -= Damage;
	if (PlayerStates[World].Hp <= 0)
	{
		PlayerStates[World].bIsAlive = false;
		EndGame(World);
	}
}

