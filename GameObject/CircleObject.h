#pragma once
#include <cstdint>
#include <memory>

#include "Math/FVector3.h"
#include "Enum.h"
#include "Texture/UTexture2D.h"

// forward declaration
class URenderer;

class CircleObject : public std::enable_shared_from_this<CircleObject>
{

public:
	CircleObject(EWorld SelectedWorld);
	virtual ~CircleObject() = default;

	virtual void Update(float DeltaTime) = 0;
	virtual void FixedUpdate(float FixedTime) = 0;
	virtual void HandleWallCollision(const FVector3& WallNormal) = 0;
	virtual void HandleBallCollision(CircleObject* OtherBall) = 0;

	virtual void Render(const URenderer& Renderer) const;

	float GetAngle() const { return Radian; }
	void SetAngle(float rad)	{ Radian = rad; }

	virtual void Move(float DeltaTime) = 0;
	virtual void OnDestroy() = 0;	// CircleObject에 의해 부가적으로 발생한 메모리만 삭제, CircleObject 객체는 ObjectManager에 의해 삭제.

	virtual void OnHit();
	
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

protected:
	EWorld MyWorld;
	std::unique_ptr<UTexture2D> Texture;

	FVector3 Location;
	FVector3 Velocity;
	float Radius = 0.0f;
	float Radian = 0.0f; // 0 == top radian으로 다룸

	int WorldWalls[2][4] = {
		{ 0 , 1 , -1 , 1},  // left right top bottom
		{-1 , 0 , -1 , 1},
	};

	FVector3 WorldOffsets[2] = {
		FVector3(0.5f , 0.0f , 0.0f),
		FVector3(-0.5f , 0.0f , 0.0f)
	};
};