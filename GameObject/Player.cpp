#include "Player.h"
#include "URenderer.h"
#include "Constant.h"

Player::Player(EWorld selectedWorld) : CircleObject(selectedWorld)
{
    Radius = 0.1f;
    //const float x = rand() % 1 - MyWorld;
    //const float y = rand() % 2 - 1;
    Location = FVector3(0 , 0 , 0);
    Velocity = FVector3(0 , 0 , 0);
    Radian = 0;
}

// 이동 후 겹침 보정 (Monster, Player에 대해)
void Player::Update(float DeltaTime)
{
    if (currentWeapon != nullptr) {
        currentWeapon->Update(DeltaTime);
    }
}

void Player::FixedUpdate(float Fixed)
{
}

BaseWeapon* Player::GetWeapon() const
{
    return currentWeapon;
}

void Player::SetWeapon(BaseWeapon* weapon)
{
    currentWeapon = weapon;
}

void Player::HandleWallCollision(const FVector3& WallNormal)
{

    if (WallNormal.x > 0.0001f) {
        // 왼쪽
        Location.x = WorldWalls[ MyWorld ][ Left ] + Radius;
    }
    else if (WallNormal.x < -0.0001f) {
        // 오른쪽
        Location.x = WorldWalls[ MyWorld ][ Right ] - Radius;
    }


    if (WallNormal.y > 0.0001f) {
        // 아래
        Location.y = WorldWalls[ MyWorld ][ Bottom ] + Radius;
    }
    else if (WallNormal.y < -0.0001f) {
        // 위
        Location.y = WorldWalls[ MyWorld ][ Top ] - Radius;
    }
}

void Player::Render(const URenderer& Renderer) const
{
    Renderer.UpdateConstant(Location , Radius, Radian);
    ID3D11Buffer* buffer = Renderer.GetVertexBuffer(EObjectType::Player);
    int NumOfVertices = Renderer.GetBufferSize(EObjectType::Player);
    if(buffer != nullptr)
    {
        Renderer.RenderPrimitive(buffer, NumOfVertices);
    }
}

void Player::Move(float DeltaTime)
{
    Location += Velocity * DeltaTime;
}


void Player::OnDestroy()
{
}

void Player::OnHit()
{

}

void Player::LevelUp()
{
    // !TODO : 레벨업 로직
}
