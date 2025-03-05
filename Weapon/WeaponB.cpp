#include "Weapon/WeaponB.h"

WeaponB::WeaponB(Player* player) : BaseWeapon(player) {
	AngularSpeed = 0.1f;
	Radian = 0.f;
	NumOfBullet = 1;
	TotalRadius = 1.f;
	BulletRadius = 1.f;
};

WeaponB::~WeaponB() {
	// 보유중인 불렛 삭제?
}

// 레벨업시, 시작시, NumOfBullet이 변할때 -> SpawnBullet

void WeaponB::Update(float DeltaTime)
{
	// Bullet 플레이어 중심 회전

	Radian += AngularSpeed;

	for (const auto& bullet : bullets) {
		float x = cos(Radian) * TotalRadius;
		float y = sin(Radian) * TotalRadius;

		bullet->SetLocation(FVector3(x , y , 0));
	}
}

void WeaponB::SpawnBullet()
{
	auto& objectManager = Singleton<ObjectManager>::GetInstance();

	BulletB* bullet = objectManager.RegistObject<BulletB>(currentPlayer->GetWorld());

	bullet->SetLocation(currentPlayer->GetLocation());
	bullet->SetAngle(currentPlayer->GetAngle());
	bullet->SetRadius(BulletRadius);
	//bullet->SetVelocity(ConvertToDirection(currentPlayer->GetAngle()) * bulletSpeed);
}