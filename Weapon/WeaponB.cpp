#include "Weapon/WeaponB.h"
#include "GameObject/Player.h"


WeaponB::WeaponB(Player* player) : BaseWeapon(player) {
	currentPlayer = player;
	AngularSpeed = 0.1f;
	Radian = 0.f;
	TotalRadius = 0.5f;
	BulletRadius = 0.1f;

	SpawnBullet(5);
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

// 레벨업시, 시작시, NumOfBullet이 변할때 -> SpawnBullet

void WeaponB::Update(float DeltaTime)
{
	// Bullet 플레이어 중심 회전

	// 0 ~ 2pi

	Radian += AngularSpeed;
	UpdateBulletLocation();
}

void WeaponB::SpawnBullet(int num = 1)
{
	for (int i = 0; i < num; i++) {
		auto& objectManager = Singleton<ObjectManager>::GetInstance();

		BulletB* bullet = objectManager.RegistObject<BulletB>(currentPlayer->GetWorld());
		bullet->SetRadius(BulletRadius);
		bullets.push_back(bullet);
	}
	
	UpdateBulletLocation();
}

void WeaponB::UpdateBulletLocation()
{
	for (int i = 0; i < bullets.size(); i++) {
		auto& bullet = bullets.at(i);
		float value = ( 2.f * 3.141592f * i ) / bullets.size();

		float x = cos(Radian + value) * TotalRadius + currentPlayer->GetLocation().x;
		float y = sin(Radian + value) * TotalRadius + currentPlayer->GetLocation().y;

		bullet->SetLocation(FVector3(x , y , 0));
	}
}