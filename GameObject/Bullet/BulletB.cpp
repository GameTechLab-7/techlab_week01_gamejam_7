#include "math.h"

#include "GameObject/Bullet/BulletB.h"
#include "URenderer.h"
#include "Manager/ObjectManager.h"
#include "GameObject/Monster.h"


// 외부에서 멤버변수 초기화
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

void BulletB::HandleBallCollision(CircleObject* OtherBall)
{
    // Bullet -> Monster
    CircleObject* object = OtherBall;
    Monster* monster = dynamic_cast< Monster* >( object );

    if (monster != nullptr) {
        monster->OnHit();

        // TODO
        // Monster.넉백
        // If Monster Die
        //		Monster.Destroy();
        //		Player.AddPoint
    }
}

void BulletB::Move(float DeltaTime)
{
}

void BulletB::OnDestroy()
{
}

void BulletB::OnHit()
{
}
