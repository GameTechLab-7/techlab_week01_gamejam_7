#pragma once

#include "Weapon/BaseWeapon.h"
#include "Manager/ObjectManager.h"
#include "GameObject/Bullet/BulletA.h"
#include "Enum.h"


// 기본 무기
class WeaponA : public BaseWeapon {
public:
	float ShootCooldown;
	float BulletSize;
	float BulletSpeed;

	WeaponA(Player* player);

	virtual void Update(float tick) override;

private:
	float Timer;
	void SpawnBullet();
	FVector3 ConvertToDirection(const float angle);
};