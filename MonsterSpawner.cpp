#include "MonsterSpawner.h"
#include <GameObject/Monster.h>
#include <Manager/ObjectManager.h>

MonsterSpawner::MonsterSpawner(SpawnerInfo Info)
	: Info(Info)
{
	CurrentMonsterNum = Info.DefaultMonsterNum;
	SpawnTime = Info.SpawnRate;
}

void MonsterSpawner::Update(float DeltaTime)
{
	// Info 기반으로 생성한다.
	SpawnTime += DeltaTime;
	IncreaseTime += DeltaTime;

	if (IncreaseTime >= Info.MonsterIncreaseTime)
	{
		CurrentMonsterNum += Info.MonsterIncreaseNum;
		IncreaseTime = 0;
	}

	if (SpawnTime >= Info.SpawnRate)
	{
		Spawn();
		SpawnTime = 0;
	}
}

void MonsterSpawner::Spawn() const
{
	for (int i = 0; i < CurrentMonsterNum; ++i)
	{
		ObjectManager::GetInstance().RegistObject<Monster>(First)->Init(0.1f, 1.f, 0.1f);
		ObjectManager::GetInstance().RegistObject<Monster>(Second)->Init(0.1f , 1.f , 0.1f);
	}
}

void MonsterSpawner::SpawnToWorld(EWorld WorldType)
{
	ObjectManager::GetInstance().RegistObject<Monster>(WorldType);
}
