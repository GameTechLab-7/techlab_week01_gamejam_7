#pragma once
#include <enum.h>
#include <memory>

struct SpawnerInfo
{
	float MonsterSpeed;
	float MonsterScale;
	// 기본 생성 몬스터 수
	float DefaultMonsterNum;
	// 생성 주기
	float SpawnRate;
	// 생성되는 몬스터가 수가 증가할 타임
	float MonsterIncreaseTime;
	// 몬스터 생성 수 증가량
	int MonsterIncreaseNum;
};

class MonsterSpawner : public std::enable_shared_from_this<MonsterSpawner>
{
public:
	MonsterSpawner(SpawnerInfo Info);
	~MonsterSpawner() = default;

	void Update(float DeltaTime);
	void Spawn(EWorld world) const;
	void SpawnToWorld(EWorld WorldType , int numOfMonster);
	void SetMonsterSpeed(float MonsterSpeed);
	void SetMonsterScale(float MonsterScale);
	void SetDefaultMonsterNum(float DefaultMonsterNum);
	void SetSpawnRate(float SpawnRate);
	void SetMonsterIncreaseTime(float MonsterIncreaseTime);
	void SetMonsterIncreaseNum(int MonsterIncreaseNum);
	
	float GetMonsterSpeed();
	float GetMonsterScale();
	float GetDefaultMonsterNum();
	float GetSpawnRate();
	float GetMonsterIncreaseTime();
	int GetMonsterIncreaseNum();
private:
	SpawnerInfo Info;
	
	int CurrentMonsterNum = 0;
	float SpawnTime = 0.f;
	float IncreaseTime = 0.f;
};