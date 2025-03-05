#include "URenderer.h"
#include "GameObject/Bullet/BulletA.h"
#include "GameObject/Monster.h"
#include "Manager/ObjectManager.h"


// 외부에서 멤버변수 초기화
BulletA::BulletA(EWorld selectedWorld) : Bullet(selectedWorld) {
    Damage = 3;
    bIsProcessingCollision = false;
}

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

void BulletA::HandleBallCollision(CircleObject* OtherBall)
{
    // TODO
    // Bullet -> Monster
    // Monster.넉백
    // If Monster Die
    //		Monster.Destroy();
    //		Player.AddPoint
    
    CircleObject* object = OtherBall;
    Monster* monster = dynamic_cast< Monster* >( object );
    if (monster != nullptr)
    {
	if (bIsProcessingCollision)
	{
		return;
	}
        // bullet
        bIsProcessingCollision = true;
        ObjectManager::GetInstance().Destroy(this);
		FVector3 Impact = CircleObject::GetCollisionImpact(monster , this);
        monster->OnHit(Impact, Damage);
    }
}

void BulletA::Move(float DeltaTime)
{
    Location += Velocity * DeltaTime;
}

void BulletA::OnDestroy()
{
}

void BulletA::OnHit(FVector3 HitForce , int Damage)
{
}
