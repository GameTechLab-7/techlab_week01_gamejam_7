#pragma once

#include "GameObject/Bullet/Bullet.h"

// 무한 탄환
// 몬스터 통과
// 벽 무시
// 피격, 벽과 무관하게 존재한다. (ex - 회전 방어)

class BulletB : public Bullet {
	
public:
	// Collision X
	BulletB(EWorld selectedWorld);
	~BulletB() = default;

	virtual void Update(float DeltaTime) override;
	virtual void FixedUpdate(float Fixed) override;

	virtual void HandleWallCollision(const FVector3& WallNormal) override;
	virtual void HandleBallCollision(CircleObject* OtherBall) override;

	virtual void Render(const URenderer& Renderer) const override;

	virtual void Move(float DeltaTime) override;
	virtual void OnDestroy() override;

	// Bullet을(를) 통해 상속됨
	void OnHit() override;
};