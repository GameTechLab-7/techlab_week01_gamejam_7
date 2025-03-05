#include "WeaponA.h"

#include <iostream>

#include "GameObject/Player.h"
#include "Manager/ObjectManager.h"


WeaponA::WeaponA(Player* player) : BaseWeapon(player) {
	BulletSize = 0.1f;
	Timer = 0.f;
	ShootCooldown = 1.f;
	BulletSpeed = 1.f;
};

void WeaponA::Update(float tick)
{
	// n초마다 탄환 생성

	if (Timer > ShootCooldown) {
		Timer = 0.f;
		SpawnBullet();
	}
	else {
		Timer += tick;
	}
}

void WeaponA::SpawnBullet()
{
	std::cout << "Spawn!\n";
	auto& objectManager = ObjectManager::GetInstance();

	BulletA* bullet = objectManager.RegistObject<BulletA>(currentPlayer->GetWorld());

	bullet->SetLocation(currentPlayer->GetLocation());
	bullet->SetAngle(currentPlayer->GetAngle());
	bullet->SetRadius(BulletSize);
	bullet->SetVelocity(ConvertToDirection(currentPlayer->GetAngle()) * BulletSpeed);
}

FVector3 WeaponA::ConvertToDirection(const float angle)
{
	FVector3 vector3;

	vector3.x = cos(angle);
	vector3.y = sin(angle);
	vector3.z = 0;

	return vector3;
}