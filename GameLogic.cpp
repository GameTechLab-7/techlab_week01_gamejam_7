#include "GameLogic.h"
#include "Manager/GameManager.h"
#include "ResultScene.h"
#include "GlobalData.h"
#include "math.h"

GameLogic::GameLogic()
{
}

GameLogic::~GameLogic()
{
}

void GameLogic::Init()
{
	PlayerStates[ First ] = { 0 , 0 , 0 , 1, MAX_PLAYER_HP, true };
	PlayerStates[ Second ] = { 0 , 0 , 0 , 1, MAX_PLAYER_HP, true };

	LvUpThreshold = BASE_LVUP_THRESHOLD;
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

int GameLogic::GetExp(EWorld World)
{
	return PlayerStates[ World ].Exp;
}

void GameLogic::AddScore(EWorld World , int Score)
{
	PlayerStates[ World ].Score += Score;
}

void GameLogic::AddExp(EWorld World , int exp)
{
	PlayerStates[ World ].Exp += exp;
	if (PlayerStates[ World ].Exp >= LvUpThreshold)
	{
		PlayerStates[ World ].Lv = min(PlayerStates[ World ].Lv + 1, MAX_LV);
		PlayerStates[ World ].Exp -= LvUpThreshold;
		LvUpThreshold += LVUP_THRESHOLD_INCREASE;
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
	GameManager::GetInstance().ChangeScene<ResultScene>();
	GameManager::GetInstance().DeadPlayerWorld = DeadPlayerWorld;
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

bool GameLogic::CanUseSpecialSkill(EWorld World)
{
	int score = GetScore(World);
	if (score >= 10)
	{
		return true;
	}
	return false;
}

void GameLogic::UseSpecialSkill(EWorld World)
{
	if (!CanUseSpecialSkill(World))
		return;

	EWorld TargetWorld = World == EWorld::First ? EWorld::Second : EWorld::First;

	int crrScore = GetScore(World);
	AddScore(World, -crrScore);
	SpawnMonsterToWorld(TargetWorld, crrScore);
}

