#include "Monster.h"
#include "URenderer.h"
#include <Scene/MainGameScene.h>
#include "Manager/GameManager.h"
#include <cassert>
#include "Player.h"

Monster::Monster(EWorld SelectedWorld) : CircleObject(SelectedWorld)
{
    // 플레이어를 찾는다
    // 현재 씬이 메인게임씬인지 먼저 검사
    MainGameScene* Scene = (MainGameScene*)GameManager::GetInstance().GetCurrentScene();

	assert(Scene != nullptr);

	Target = Scene->GetPlayer(SelectedWorld);
}

void Monster::Update(float DeltaTime)
{

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
        otherPlayer->OnHit();
    }
}

void Monster::Render(const URenderer& Renderer) const
{
    Renderer.UpdateConstant(Location , Radius , Radian);
    ID3D11Buffer* buffer = Renderer.GetVertexBuffer(EObjectType::Enemy);
    int NumOfVertices = Renderer.GetBufferSize(EObjectType::Enemy);
    if (buffer != nullptr)
    {
        Renderer.RenderPrimitive(buffer , NumOfVertices);
    }
}

void Monster::Move(float DeltaTime)
{
    // target pos 방향으로 이동
	FVector3 Direction = Target->GetLocation() - Location;
	Direction = Direction.Normalize();

	Location += Direction * Speed * DeltaTime;
}

void Monster::OnDestroy()
{
    //
}

// TODO Bullet A, B에서 넘어옴.
void Monster::OnHit()
{
    // Monster.넉백
    // If Monster Die (Damage, 넉백 float 수치?)
    //		Monster.Destroy();
    //		Player.AddPoint
    //		Player.GetLevelPoint()
    
    if (IsDead()) {
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
    return true;
}