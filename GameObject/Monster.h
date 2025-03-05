#pragma once
#include "CircleObject.h"


class Monster : public CircleObject
{
    virtual void Update(float DeltaTime) override;
    virtual void FixedUpdate(float Fixed) override;

    virtual void HandleBallCollision(CircleObject& OtherBall) override;
};
