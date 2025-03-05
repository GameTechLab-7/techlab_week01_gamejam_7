#pragma once

#include "GameObject/Bullet/Bullet.h"

// 기본 탄환
// 몬스터 피격시 삭제
// 데미지 및 반동?

class BulletA : public Bullet {
public:
    virtual void Update(float DeltaTime) override;
    virtual void FixedUpdate(float Fixed) override;

    virtual void HandleWallCollision(const FVector3& WallNormal) override;
    virtual void HandleBallCollision(CircleObject& OtherBall) override;

    virtual void Render(const URenderer& Renderer) const override;

    virtual void Move(float DeltaTime) override;
    virtual void OnDestroy() override;
};