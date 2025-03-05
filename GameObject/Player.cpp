#include "Player.h"
#include "URenderer.h"
#include "Constant.h"
#include "Manager/GameManager.h"

Player::Player(EWorld selectedWorld) : CircleObject(selectedWorld)
{
    Radius = 0.1f;
    //const float x = rand() % 1 - MyWorld;
    //const float y = rand() % 2 - 1;
    Location = FVector3(0 , 0 , 0);
    Velocity = FVector3(0 , 0 , 0);
    Radian = 0;

    bIsHitInvisible = false;
    HitInvisibleTime = 0.5f;
}

// 이동 후 겹침 보정 (Monster, Player에 대해)
void Player::Update(float DeltaTime)
{
    if (currentWeapon != nullptr) {
        currentWeapon->Update(DeltaTime);
    }

	if (bIsHitInvisible)
	{
		HitTimer += DeltaTime;
		if (HitTimer >= HitInvisibleTime)
		{
			bIsHitInvisible = false;
			HitTimer = 0.0f;
		}
	}
}

void Player::FixedUpdate(float Fixed)
{
}

BaseWeapon* Player::GetWeapon() const
{
    if (currentWeapon == nullptr) {
        return nullptr;
    }
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
    Renderer.UpdateConstant(Location , Radius, Radian, bIsHitInvisible);
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

void Player::OnHit(FVector3 HitForce , int Damage)
{
	if (bIsHitInvisible)
	{
		return;
	}

    CircleObject::OnHit(HitForce , Damage);
	bIsHitInvisible = true;

    GameManager::GetInstance().GetLogic()->OnPlayerHit(this->GetWorld(), Damage);
}

#include <iostream>

// Player에서는 Logic을 알지 못하도록 값을 직접 넣어줌.
void Player::LevelUp(const int level) const
{
    std::cout << "Level Up! " << GetWorld() << " " << level << '\n';
    currentWeapon->SetLevel(level);
}
