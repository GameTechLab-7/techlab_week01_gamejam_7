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
    void OnHit() override;

protected:
    Player* Target;
    float InitialDistanceFromPlayer = 1.0f;
    float Speed = 0.1f;

public:
    virtual void Init(float Radius, float InitialDistance , float Speed);
};
