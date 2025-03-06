#include "Player.h"
#include "URenderer.h"
#include "Constant.h"
#include "GlobalData.h"
#include "Manager/GameManager.h"
#include "Manager/ResourceManager.h"

Player::Player(EWorld selectedWorld) : CircleObject(selectedWorld)
{
    Radius = 0.05f;
    //const float x = rand() % 1 - MyWorld;
    //const float y = rand() % 2 - 1;
    Location = FVector3(0 , 0 , 0);
    Velocity = FVector3(0 , 0 , 0);
	Acceleration = FVector3(0 , 0 , 0);

    Radian = 0;

    Texture = ResourceManager::GetInstance().LoadTargaFromFile("Assets/Texture/red.tga");
    Texture->SetPrimitiveType(EObjectType::Player);

    bIsHitInvisible = false;
    HitInvisibleTime = PLAYER_HIT_INVISIBLE_TIME;
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
            bCanMove = true;
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

void Player::HandleBallCollision(CircleObject* OtherBall)
{
    CircleObject::HandleBallCollision(OtherBall);
}

void Player::Move(float DeltaTime)
{
    Velocity += Acceleration * DeltaTime;

    Location += Velocity * DeltaTime;
    Velocity *= Drag;
    Acceleration *= Drag;

	if (Velocity.Length() < 0.0001f)
	{
		Velocity = FVector3(0 , 0 , 0);
	}

    if (Acceleration.Length() < 0.0001f)
    {
        Velocity = FVector3(0 , 0 , 0);
    }
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

    bCanMove = false;
    GameManager::GetInstance().GetLogic()->OnPlayerHit(this->GetWorld(), Damage);
}

// Player에서는 Logic을 알지 못하도록 값을 직접 넣어줌.
void Player::SetLevel(const int level) const
{
    currentWeapon->SetLevel(level);
}
