#pragma once

#include "GameObject/CircleObject.h"
#include "Weapon/BaseWeapon.h"

class Player : public CircleObject
{
private:
    BaseWeapon* currentWeapon = nullptr;
    bool bCanMove = true;

public:
    Player(EWorld selectedWorld);


    BaseWeapon* GetWeapon() const;
    void SetWeapon(BaseWeapon* weapon);

    virtual void Update(float DeltaTime) override;
    virtual void FixedUpdate(float Fixed) override;

    virtual void HandleWallCollision(const FVector3& WallNormal) override;


    virtual void Render(const URenderer& Renderer) const override;

    virtual void Move(float DeltaTime) override;

    virtual void OnDestroy() override;

    // CircleObject을(를) 통해 상속됨
    void OnHit(FVector3 HitForce , int Damage) override;

    void LevelUp(const int level) const;

	void SetCanMove(bool bCanMove) { this->bCanMove = bCanMove; }
	bool CanMove() const { return bCanMove; }

};
