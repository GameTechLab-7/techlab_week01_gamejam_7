#include "GameObject/Bullet/BulletB.h"
#include "URenderer.h"
#include "Manager/ObjectManager.h"


BulletB::BulletB(EWorld selectedWorld) : Bullet(selectedWorld) {
}


void BulletB::Update(float DeltaTime)
{
}

void BulletB::FixedUpdate(float Fixed)
{
}

void BulletB::HandleWallCollision(const FVector3& WallNormal)
{
}

void BulletB::HandleBallCollision(CircleObject& OtherBall)
{
    // Bullet -> Monster
    
    // if(OtherBall == Monster)
    // Monster.넉백
    // If Monster Die
    //		Monster.Destroy();
    //		Player.AddPoint
}

void BulletB::Render(const URenderer& Renderer) const
{
    //Renderer.UpdateConstant(Location, Radius, Radian);
}

void BulletB::Move(float DeltaTime)
{
    //Location += Velocity * DeltaTime;
}

void BulletB::OnDestroy()
{
}

void BulletB::OnHit()
{
}
