#include "MainGameScene.h"
#include "GameObject/Player.h"
#include "Manager/ObjectManager.h"
#include "Manager/GameManager.h"
#include "MonsterSpawner.h"
#include "Weapon/WeaponA.h"


void MainGameScene::LoadScene()
{
	LeftPlayer = ObjectManager::GetInstance().RegistObject<Player>(First);
	WeaponA * leftWeapon = new WeaponA(LeftPlayer);

	LeftPlayer->SetWeapon(leftWeapon);
	RightPlayer = ObjectManager::GetInstance().RegistObject<Player>(Second);
	WeaponA* rightWeapon = new WeaponA(RightPlayer);

	RightPlayer->SetWeapon(rightWeapon);

	SpawnerInfo Info;
	Info.DefaultMonsterNum = 5;
	Info.SpawnRate = 3.0f;
	Info.MonsterIncreaseTime = 5.0f;
	Info.MonsterIncreaseNum = 1;

	Spawner = std::make_shared<MonsterSpawner>(Info);
}

void MainGameScene::ExitScene()
{
	ObjectManager::GetInstance().Destroy(LeftPlayer);
	ObjectManager::GetInstance().Destroy(RightPlayer);
}

void MainGameScene::Update(float DeltaTime)
{
	BaseScene::Update(DeltaTime);
	ObjectManager::GetInstance().Update(DeltaTime);
	Spawner->Update(DeltaTime);
}

void MainGameScene::Render()
{
}

Player* MainGameScene::GetPlayer(EWorld WorldType) const
{
	if (WorldType == EWorld::First)
	{
		return LeftPlayer;
	}
	else
	{
		return RightPlayer;
	}
}
