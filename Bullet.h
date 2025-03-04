#pragma once

#include "CircleObject.h"

class Bullet : public CircleObject
{
public:
    Bullet(EWorld selectedWorld) : CircleObject(selectedWorld) {}

    virtual void HandleWallCollision(const FVector3& WallNormal) override;
    virtual void HandleBallCollision(CircleObject& OtherBall) override;
};