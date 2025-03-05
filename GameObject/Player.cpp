#include "Player.h"
#include "URenderer.h"

// 문제 1. 벽 겹침 보정을 언제 어디서 해주냐


// Move 이후? 뭐 어디서? 

Player::Player(EWorld selectedWorld) : CircleObject(selectedWorld)
{
    Radius = 0.3f;
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

    // 벽
    if (Location.x - Radius < WorldWalls[MyWorld][Left])
    {
        Location.x = WorldWalls[MyWorld][Left] + Radius;
    }
    else if (Location.x + Radius > WorldWalls[MyWorld][Right])
    {
        Location.x = WorldWalls[MyWorld][Right] - Radius;
    }

    if (Location.y - Radius < WorldWalls[MyWorld][Top])
    {
        Location.y = WorldWalls[MyWorld][Top] + Radius;
    }
    else if (Location.y + Radius > WorldWalls[MyWorld][Bottom])
    {
        Location.y = WorldWalls[MyWorld][Bottom] - Radius;
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
}

void Player::HandleBallCollision(CircleObject& OtherBall)
{
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
