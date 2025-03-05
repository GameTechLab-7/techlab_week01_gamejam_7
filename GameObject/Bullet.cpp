#include "Bullet.h"
#include "URenderer.h"

void Bullet::Update(float DeltaTime)
{
}

void Bullet::FixedUpdate(float Fixed)
{
}

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

void Bullet::Render(const URenderer& Renderer) const
{
    Renderer.UpdateConstant(Location, Radius, Radian);
}

void Bullet::Move(float DeltaTime)
{
    Location += Velocity * DeltaTime;
}

void Bullet::OnDestroy()
{
}
