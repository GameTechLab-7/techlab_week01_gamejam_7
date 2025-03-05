#include "GameObject/Bullet.h"
#include "URenderer.h"
#include "Monster.h"
#include "Manager/ObjectManager.h"
#include <iostream>

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


    /*CircleObject* object = &OtherBall;
    Monster* monster = dynamic_cast< Monster* >( object );
    if (monster != nullptr)
    {
		
        monster->OnHit();
    }*/

}

void Bullet::Render(const URenderer& Renderer) const
{
    Renderer.UpdateConstant(Location , Radius, Radian);
    ID3D11Buffer* buffer = Renderer.GetVertexBuffer(EObjectType::Bullet);
    int NumOfVertices = Renderer.GetBufferSize(EObjectType::Bullet);
    if(buffer != nullptr)
    {
        Renderer.RenderPrimitive(buffer, NumOfVertices);
    }
}

void Bullet::Move(float DeltaTime)
{
    Location += Velocity * DeltaTime;
}

void Bullet::OnDestroy()
{
}

void Bullet::OnHit()
{
    std::cout << "Bullet Hit" << std::endl;
    ObjectManager::GetInstance().Destroy(this);
}
