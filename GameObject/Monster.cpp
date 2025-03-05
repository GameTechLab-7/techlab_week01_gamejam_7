#include "Monster.h"
#include "URenderer.h"
#include "Scene/MainGameScene.h"
#include "Manager/GameManager.h"
#include "Player.h"

#include <iostream>
#include <cassert>


Monster::Monster(EWorld SelectedWorld) : CircleObject(SelectedWorld)
{
    // 플레이어를 찾는다
    // 현재 씬이 메인게임씬인지 먼저 검사
    MainGameScene* Scene = static_cast<MainGameScene*>(GameManager::GetInstance().GetCurrentScene());

	assert(Scene != nullptr);

	Target = Scene->GetPlayer(SelectedWorld);
	Texture->SetPrimitiveType(EObjectType::Enemy);
    HitInvisibleTime = 0.2f;

    Drag = 0.5f;
	Acceleration = FVector3(0 , 0 , 0);
}

void Monster::Update(float DeltaTime)
{
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

void Monster::FixedUpdate(float Fixed)
{
}

void Monster::HandleBallCollision(CircleObject* OtherBall)
{
    // Bullet -> Monster (Bullet)

    // Monster -> Player (Monster)

    // Monster - Monster (Monster)


    CircleObject* object = OtherBall;
    // !TODO : 다른 몬스터와 충돌했을 때 처리. 그냥 밀어내면될듯 ->이거해도되나
	Monster* otherMontser = dynamic_cast< Monster* >( object );
	if (otherMontser != nullptr)
	{
        // !Note : 큐브는 어색하다
		ResolveOverlap(*otherMontser);
	}
    
    
    // !TODO : 다른 몬스터와 충돌했을 때 처리. 그냥 밀어내면될듯 ->이거해도되나
    Player* otherPlayer = dynamic_cast< Player* >( object );
    if (otherPlayer != nullptr)
    {
        // Player 밀기
        // 몬스터 밀기
        // Player 데미지
        // Player 무적
		FVector3 HitImpact = CircleObject::GetCollisionImpact(otherPlayer , this);
        otherPlayer->OnHit(HitImpact, 1);
    }
}

void Monster::Move(float DeltaTime)
{
    // target pos 방향으로 이동
	FVector3 Direction = Target->GetLocation() - Location;
	SetVelocity(Direction.Normalize() * Speed);

    Velocity += Acceleration * DeltaTime;
	Location += Velocity * DeltaTime;

    Acceleration *= Drag;
    if (Acceleration.Length() < 0.0001f)
    {
        Acceleration = FVector3(0 , 0 , 0);
    }
}

void Monster::OnDestroy()
{
    //
}

// TODO Bullet A, B에서 넘어옴.
void Monster::OnHit(FVector3 HitForce , int Damage)
{
    // Monster.넉백
    // If Monster Die (Damage, 넉백 float 수치?)
    //		Monster.Destroy();
    //		Player.AddPoint
    //		Player.GetLevelPoint()
	if (bIsHitInvisible)
	{
		return;
	}

    CircleObject::OnHit(HitForce , Damage);
    bIsHitInvisible = true;
    //SetLocation(GetLocation() + HitForce);
    
    std::cout << "Damage to Monster" << Damage << std::endl;
	HP -= Damage;

    if (IsDead()) {
        std::cout << "destroy! \n";

        auto* logic = GameManager::GetInstance().GetLogic();
        logic->AddScore(GetWorld(), DropScore);
        logic->AddExp(GetWorld(), DropExp);
        ObjectManager::GetInstance().Destroy(this);
    }
}

void Monster::Init(float Radius, float InitialDistance , float Speed)
{
    this->Radius = Radius;
	this->Speed = Speed;

	InitialDistanceFromPlayer = InitialDistance;

	// 플레이어 위치에서 일정 거리 떨어진 랜덤 위치에 생성
	FVector3 PlayerLocation = Target->GetLocation();
	Location = PlayerLocation + FVector3::GetRandomUnitVector2D() * InitialDistance;
}

bool Monster::IsDead() {
	return HP <= 0;
}