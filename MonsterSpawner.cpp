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
		for (int i = 0; i < CurrentMonsterNum; ++i)
		{
			Spawn(First);
			Spawn(Second);
		}
		SpawnTime = 0;
	}
}

void MonsterSpawner::Spawn(EWorld world) const
{
	ObjectManager::GetInstance().RegistObject<Monster>(world)->Init(0.1f * Info.MonsterScale , 1.f , 0.1f * Info.MonsterSpeed);
}

void MonsterSpawner::SpawnToWorld(EWorld WorldType, int numOfMonster)
{
	for (int i = 0; i < numOfMonster; i++)
		Spawn(WorldType);
}

void MonsterSpawner::SetMonsterSpeed(float MonsterSpeed)
{
	Info.MonsterSpeed = MonsterSpeed;
}

void MonsterSpawner::SetMonsterScale(float MonsterScale)
{
	Info.MonsterScale = MonsterScale;
}

void MonsterSpawner::SetDefaultMonsterNum(float DefaultMonsterNum)
{
	Info.DefaultMonsterNum = DefaultMonsterNum;
}

void MonsterSpawner::SetSpawnRate(float SpawnRate)
{
	Info.SpawnRate = SpawnRate;
}

void MonsterSpawner::SetMonsterIncreaseTime(float MonsterIncreaseTime)
{
	Info.MonsterIncreaseTime = MonsterIncreaseTime;
}

void MonsterSpawner::SetMonsterIncreaseNum(int MonsterIncreaseNum)
{
	Info.MonsterIncreaseNum = MonsterIncreaseNum;
}

float MonsterSpawner::GetMonsterSpeed()
{
	return Info.MonsterSpeed;
}

float MonsterSpawner::GetMonsterScale()
{
	return Info.MonsterScale;
}

float MonsterSpawner::GetDefaultMonsterNum()
{
	return Info.DefaultMonsterNum;
}

float MonsterSpawner::GetSpawnRate()
{
	return Info.SpawnRate;
}

float MonsterSpawner::GetMonsterIncreaseTime()
{
	return Info.MonsterIncreaseTime;
}

int MonsterSpawner::GetMonsterIncreaseNum()
{
	return Info.MonsterIncreaseNum;
}
