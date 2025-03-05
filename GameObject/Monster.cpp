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

void Monster::FixedUpdate(float Fixed)
{
}

void Monster::HandleBallCollision(CircleObject& OtherBall)
{
    // Monster 끼리 충돌 시 보정
    
    // Monster -> Player
    // 서로 Monster, Player 넉백 -> velocity
    // Player Damage 
    // Player 무적 
    
    // Monster - Monster
    // if Ball is Monster
    //	 충돌 위치 보정
}
