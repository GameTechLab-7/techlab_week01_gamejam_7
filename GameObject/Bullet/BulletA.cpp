#include "GameObject/Bullet/BulletA.h"
#include "URenderer.h"
#include "Manager/ObjectManager.h"

void BulletA::Update(float DeltaTime)
{
}

void BulletA::FixedUpdate(float Fixed)
{
}

void BulletA::HandleWallCollision(const FVector3& WallNormal)
{
    // 탄환 -> 벽 막힘
    ObjectManager::GetInstance().Destroy(this);
}

void BulletA::HandleBallCollision(CircleObject& OtherBall)
{
    // Bullet -> Monster
    ObjectManager::GetInstance().Destroy(this);
    // Monster.넉백
    // If Monster Die
    //		Monster.Destroy();
    //		Player.AddPoint
}

void BulletA::Render(const URenderer& Renderer) const
{
    Renderer.UpdateConstant(Location, Radius, Radian);
}

void BulletA::Move(float DeltaTime)
{
    Location += Velocity * DeltaTime;
}

void BulletA::OnDestroy()
{
}
