#pragma once

#include "Weapon/BaseWeapon.h"
#include "Manager/ObjectManager.h"
#include "GameObject/Bullet/BulletA.h"
#include "Enum.h"
#include "Weapon/WeaponAData.h"


// 기본 무기
class WeaponA : public BaseWeapon {
public:
	WeaponAData WeaponData;

	WeaponA(Player* player);

	virtual void Update(float tick) override;
	virtual void SetLevel(const int level) override;

private:
	float Timer;
	void SpawnBullet();
	FVector3 ConvertToDirection(const float angle);
};