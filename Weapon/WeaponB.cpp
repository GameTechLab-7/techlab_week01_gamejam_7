#include "Weapon/WeaponB.h"
#include "GameObject/Player.h"


WeaponB::WeaponB(Player* player) : BaseWeapon(player) {
	currentPlayer = player;
	SetLevel(1);
	Radian = 0.f;

	SpawnBullet(WeaponData.NumOfBullets);
};

// 보유중인 Bullet은 Object
WeaponB::~WeaponB() {
	// 보유중인 불렛 삭제?
	auto& objectManager = Singleton<ObjectManager>::GetInstance();
	for (auto& bullet : bullets) {
		objectManager.Destroy(bullet);
	}
	bullets.clear();
}

void WeaponB::Update(float DeltaTime)
{
	// Bullet 플레이어 중심 회전

	// 0 ~ 2pi

	Radian += WeaponData.AngularSpeed / WeaponData.TotalRadius * DeltaTime;
	UpdateBulletLocation();
}

void WeaponB::Clear() {
	auto& objectManager = Singleton<ObjectManager>::GetInstance();
	for (auto& bullet : bullets) {
		objectManager.Destroy(bullet);
	}
	bullets.clear();
}

void WeaponB::SpawnBullet(int num = 1)
{
	for (int i = 0; i < num; i++) {
		auto& objectManager = Singleton<ObjectManager>::GetInstance();

		BulletB* bullet = objectManager.RegistObject<BulletB>(currentPlayer->GetWorld());
		bullet->SetRadius(WeaponData.BulletRadius);
		bullets.push_back(bullet);
	}
	
	UpdateBulletLocation();
}

void WeaponB::UpdateRadius() {
	for (auto& bullet : bullets) {
		bullet->SetRadius(WeaponData.BulletRadius);
	}
}

void WeaponB::UpdateBulletLocation()
{
	for (int i = 0; i < bullets.size(); i++) {
		auto& bullet = bullets.at(i);
		float value = ( 2.f * 3.141592f * i ) / bullets.size();

		float x = cos(Radian + value) * WeaponData.TotalRadius + currentPlayer->GetLocation().x;
		float y = sin(Radian + value) * WeaponData.TotalRadius + currentPlayer->GetLocation().y;

		bullet->SetLocation(FVector3(x , y , 0));
	}
}

void WeaponB::SetLevel(const int level) {
	WeaponData = WeaponBDataLvTable[ level ];

	// Level에 맞게 업데이트
	Clear();
	SpawnBullet(WeaponData.NumOfBullets);
	UpdateRadius();
}