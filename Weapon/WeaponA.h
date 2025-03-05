#pragma once

#include "BaseWeapon.h"
#include "Manager/ObjectManager.h"
#include "GameObject/Bullet.h"
#include "Enum.h"


class WeaponA : public BaseWeapon {
public:
	float timer;
	float shootCooldown;
	float bulletSize;


	WeaponA(Player* player);


	virtual void Update(float tick) override;

private:
	void SpawnBullet();
	FVector3 ConvertToDirection(const float angle);
};