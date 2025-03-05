#include "Weapon/WeaponC.h"

//WeaponC::WeaponC(Player* player) : BaseWeapon(player) {
//	AngularSpeed = 0.1f;
//	Radian = 0.f;
//	NumOfBullet = 1;
//	TotalRadius = 1.f;
//	BulletRadius = 1.f;
//};
//
//void WeaponC::Update(float tick)
//{
//	// n초마다 탄환 생성
//
//	if (timer > shootCooldown) {
//		timer = 0.f;
//		SpawnBullet();
//	}
//	else {
//		timer += tick;
//	}
//}
//
//void WeaponC::SpawnBullet()
//{
//	auto& objectManager = Singleton<ObjectManager>::GetInstance();
//
//	BulletA* bullet = objectManager.RegistObject<BulletA>(currentPlayer->GetWorld());
//
//	bullet->SetLocation(currentPlayer->GetLocation());
//	bullet->SetAngle(currentPlayer->GetAngle());
//	bullet->SetRadius(bulletSize);
//	bullet->SetVelocity(ConvertToDirection(currentPlayer->GetAngle()) * bulletSpeed);
//}