#include "GameObject/Bullet/BulletB.h"
#include "URenderer.h"
#include "Manager/ObjectManager.h"

void BulletB::Update(float DeltaTime)
{
}

void BulletB::FixedUpdate(float Fixed)
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
    Renderer.UpdateConstant(Location, Radius, Radian);
}

void BulletB::Move(float DeltaTime)
{
    Location += Velocity * DeltaTime;
}

void BulletB::OnDestroy()
{
}
