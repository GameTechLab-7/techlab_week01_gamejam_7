#pragma once
#include "CircleObject.h"

class Player;

class Monster : public CircleObject
{
public:
    Monster(EWorld SelectedWorld);
    virtual ~Monster() = default;

    virtual void Update(float DeltaTime) override;
    virtual void FixedUpdate(float Fixed) override;

    virtual void HandleBallCollision(CircleObject* OtherBall) override;

    void Render(const URenderer& Renderer) const override;
    void Move(float DeltaTime) override;
    void OnDestroy() override;
    void OnHit(FVector3 HitForce , int Damage) override;

protected:
    Player* Target;
    int HP = 5;
    float InitialDistanceFromPlayer = 1.0f;
    float Speed = 0.1f;
    float DropExp = 1;
    float DropScore = 1;

protected:
    bool IsDead();

public:
    virtual void Init(float Radius, float InitialDistance , float Speed);

};
