#pragma once
#include "GameObject/CircleObject.h"


class Bullet : public CircleObject
{
public:
    Bullet(EWorld selectedWorld) : CircleObject(selectedWorld)
    {
    }

    virtual void Update(float DeltaTime) = 0;
    virtual void FixedUpdate(float Fixed) = 0;

    virtual void HandleWallCollision(const FVector3& WallNormal) = 0;
    virtual void HandleBallCollision(CircleObject& OtherBall) = 0;

    virtual void Render(const URenderer& Renderer) const = 0;

    virtual void Move(float DeltaTime) = 0;
    virtual void OnDestroy() = 0;
};
