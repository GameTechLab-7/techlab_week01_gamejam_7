#pragma once

#include "GameObject/CircleObject.h"
#include "BaseWeapon.h"

class Player : public CircleObject
{
private:
    BaseWeapon* currentWeapon;

public:
    Player(EWorld selectedWorld);


    BaseWeapon* GetWeapon();
    void SetWeapon(BaseWeapon* weapon);

    virtual void Update(float DeltaTime) override;
    virtual void FixedUpdate(float Fixed) override;

    virtual void HandleWallCollision(const FVector3& WallNormal) override;

    virtual void HandleBallCollision(CircleObject& OtherBall) override;


    virtual void Render(const URenderer& Renderer) const override;

    virtual void Move(float DeltaTime) override;

    virtual void OnDestroy() override;
};
