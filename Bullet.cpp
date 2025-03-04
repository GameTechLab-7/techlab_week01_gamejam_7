#include "Bullet.h"

void Bullet::HandleWallCollision(const FVector3& WallNormal)
{
    // 탄환 -> 벽 막힘
}

void Bullet::HandleBallCollision(CircleObject& OtherBall)
{
    // Bullet -> Monster
    // ObjectManager::Get().Destory(bullet)
    // Monster.넉백
    // If Monster Die
    //		Monster.Destroy();
    //		Player.AddPoint
}
