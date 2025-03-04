#pragma once
#include "CircleObject.h"


class Monster : public CircleObject
{
    void Update(float DeltaTime);
    virtual void HandleBallCollision(CircleObject& OtherBall) override;
};
