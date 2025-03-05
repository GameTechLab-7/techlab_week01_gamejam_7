#include "WeaponA.h"

#include <iostream>

#include "GameObject/Player.h"
#include "Manager/ObjectManager.h"




// 레벨별 웨폰 데이터

WeaponA::WeaponA(Player* player) : BaseWeapon(player) {
	SetLevel(1);
	Timer = 0.f;
};

void WeaponA::Update(float tick)
{
	// n초마다 탄환 생성

	if (Timer > WeaponData.ShootCooldown) {
		Timer = 0.f;
		SpawnBullet();
	}
	else {
		Timer += tick;
	}
}

void WeaponA::SpawnBullet()
{
	std::cout << WeaponData.BulletSpeed << '\n';
	auto& objectManager = ObjectManager::GetInstance();

	BulletA* bullet = objectManager.RegistObject<BulletA>(currentPlayer->GetWorld());

	bullet->SetLocation(currentPlayer->GetLocation());
	bullet->SetAngle(currentPlayer->GetAngle());
	bullet->SetRadius(WeaponData.BulletSize);
	bullet->SetForce(WeaponData.Force);
	bullet->SetVelocity(ConvertToDirection(currentPlayer->GetAngle()) * WeaponData.BulletSpeed);
}

FVector3 WeaponA::ConvertToDirection(const float angle)
{
	FVector3 vector3;

	vector3.x = cos(angle);
	vector3.y = sin(angle);
	vector3.z = 0;

	return vector3;
}

void WeaponA::SetLevel(const int level) {
	WeaponData = WeaponADataLvTable[ level ];
}