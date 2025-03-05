#include "WeaponA.h"

#include <iostream>

WeaponA::WeaponA(Player* player) : BaseWeapon(player) {
	bulletSize = 0.1f;
	timer = 0.f;
	shootCooldown = 1.f;
};

void WeaponA::Update(float tick)
{
	// n초마다 탄환 생성

	if (timer > shootCooldown) {
		timer = 0.f;
		SpawnBullet();
	}
	else {
		timer += tick;
	}
}

void WeaponA::SpawnBullet()
{
	std::cout << "Spawn!\n";
	auto& objectManager = Singleton<ObjectManager>::GetInstance();

	Bullet* bullet = objectManager.RegistObject<Bullet>(currentPlayer->GetWorld());

	bullet->SetLocation(currentPlayer->GetLocation());
	bullet->SetAngle(currentPlayer->GetAngle());
	bullet->SetRadius(bulletSize);
	bullet->SetVelocity(ConvertToDirection(currentPlayer->GetAngle()));
}

FVector3 WeaponA::ConvertToDirection(const float angle)
{
	FVector3 vector3;

	vector3.x = cos(angle);
	vector3.y = sin(angle);
	vector3.z = 0;

	return vector3;
}