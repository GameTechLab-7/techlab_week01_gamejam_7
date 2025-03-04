#pragma once

#include "GameObject/CircleObject.h"

class Player : public CircleObject
{
public:
    Player(EWorld selectedWorld);

    void Update(float DeltaTime);

    virtual void HandleWallCollision(const FVector3& WallNormal) override;

    virtual void HandleBallCollision(CircleObject& OtherBall) override;


    virtual void Render(const URenderer& Renderer) const override;

    virtual void Move(float DeltaTime) override;

    virtual void OnDestroy() override;
};
