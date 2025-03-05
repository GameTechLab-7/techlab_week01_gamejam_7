#pragma once
#include "math.h"
#include <vector>


#include "Weapon/BaseWeapon.h"
#include "Math/FVector3.h"
#include "Manager/ObjectManager.h"
#include "GameObject/Bullet/BulleB.h"

// 회전
class WeaponB : public BaseWeapon {
	// 회전속도
	// 회전각 (Radian)
	// 개수
	// 반지름 (전체)
	// 반지름 (물체)
public:
	std::vector<BulletB*> bullets;
	float AngularSpeed;
	float Radian;
	unsigned int NumOfBullet;
	float TotalRadius;
	float BulletRadius;

	WeaponB(Player* player);
	~WeaponB();


	virtual void Update(float DeltaTime) override;
	
private:
	void SpawnBullet();
	void DestroyBullet();
};