#include "URenderer.h"
#include "GameObject/Bullet/BulletB.h"
#include "GameObject/Monster.h"
#include "Manager/ObjectManager.h"


// 외부에서 멤버변수 초기화
BulletB::BulletB(EWorld selectedWorld) : Bullet(selectedWorld) {

}

void BulletB::HandleWallCollision(const FVector3& WallNormal)
{
}

void BulletB::HandleBallCollision(CircleObject* OtherBall)
{
    CircleObject* object = OtherBall;
    Monster* monster = dynamic_cast< Monster* >( object );
    if (monster != nullptr)
    {
        monster->OnHit();
    }
}

void BulletB::Update(float DeltaTime)
{
}

void BulletB::FixedUpdate(float FixedTime)
{
}

void BulletB::Move(float DeltaTime)
{
}

void BulletB::OnDestroy()
{
}
