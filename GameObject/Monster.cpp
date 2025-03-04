#include "Monster.h"


void Monster::Update(float DeltaTime)
{
    // 벽
    if (Location.x - Radius < WorldWalls[MyWorld][Left])
    {
        Location.x = WorldWalls[MyWorld][Left] + Radius;
    }
    else if (Location.x + Radius > WorldWalls[MyWorld][Right])
    {
        Location.x = WorldWalls[MyWorld][Right] - Radius;
    }

    if (Location.y - Radius < WorldWalls[MyWorld][Top])
    {
        Location.y = WorldWalls[MyWorld][Top] + Radius;
    }
    else if (Location.y + Radius > WorldWalls[MyWorld][Bottom])
    {
        Location.y = WorldWalls[MyWorld][Bottom] - Radius;
    }
}

void Monster::HandleBallCollision(CircleObject& OtherBall)
{
    // Monster - Monster
    // if Ball is Monster
    //	 충돌 위치 보정
}
