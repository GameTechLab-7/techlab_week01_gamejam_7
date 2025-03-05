#pragma once
#include <cstdint>
#include <memory>

#include "Math/FVector3.h"
#include "Enum.h"

// forward declaration
class URenderer;

class CircleObject : public std::enable_shared_from_this<CircleObject>
{

public:
	CircleObject(EWorld SelectedWorld);
	virtual ~CircleObject() = default;

	virtual void Update(float DeltaTime) = 0;
	virtual void FixedUpdate(float FixedTime) = 0;
	virtual void HandleWallCollision(const FVector3& WallNormal);
	virtual void HandleBallCollision(CircleObject* OtherBall);

	virtual void Render(const URenderer& Renderer) const = 0;

	float GetAngle() const { return Radian; }
	void SetAngle(float rad)	{ Radian = rad; }

	virtual void Move(float DeltaTime) = 0;
	virtual void OnDestroy() = 0;	// CircleObject에 의해 부가적으로 발생한 메모리만 삭제, CircleObject 객체는 ObjectManager에 의해 삭제.

	virtual void OnHit(FVector3 HitForce, int Damage);
	
	void ResolveOverlap(CircleObject& OtherBall);

public:
	FVector3 GetLocation() const { return Location; }
	void SetLocation(const FVector3& NewLocation) { Location = NewLocation; }

	FVector3 GetVelocity() const { return Velocity; }
	void SetVelocity(const FVector3& NewVelocity) { Velocity = NewVelocity; }

	void AddVelocity(const FVector3& AddVelocity) { Velocity += AddVelocity; }

	float GetRadius() const { return Radius; }
	void SetRadius(float NewRadius) { Radius = NewRadius; }

	EWorld GetWorld() const { return MyWorld; }

	// 피격 시 충돌 임팩트를 생성함. 방향은 HitObject -> HitByObject 
	static FVector3 GetCollisionImpact(CircleObject* HitByObject, CircleObject* HitObject);

	void SetAccel(FVector3 Acceleration)
	{ 
		this->Acceleration = Acceleration; 
	}

protected:
	FVector3 Location;
	FVector3 Velocity;
	FVector3 Acceleration;

	float Radius = 0.0f;
	float Radian = 0.0f; // 0 == top radian으로 다룸

	float Drag = 0.5f;

	EWorld MyWorld;

	FVector3 WorldOffsets[2] = {
		FVector3(0.5f , 0.0f , 0.0f),
		FVector3(-0.5f , 0.0f , 0.0f)
	};

	bool bIsProcessingCollision = false;

	// 피격 시 무적
	bool bIsHitInvisible = false;
	float HitInvisibleTime = 0.0f;
	float HitTimer = 0.0f;
public:
	void SetCollisionFlag(bool Flag) { bIsProcessingCollision = Flag; }
	bool IsCollisionProcessing() const { return bIsProcessingCollision; }
};