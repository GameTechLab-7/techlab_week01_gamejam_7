#pragma once
#include "FVector3.h"
#include <d3d11.h>
#include "URenderer.h"

enum World {
	first,
	second,
};

enum Dir {
	left,
	right,
	top,
	bottom,
};

class CircleObject {
public:
	FVector3 Location;
	FVector3 Velocity;
	float Radius;

	float Friction = 0.01f;      // 마찰 계수
	float BounceFactor = 0.85f;  // 반발 계수

	bool bApplyGravity = false;
	static float Gravity;

	World MyWorld;
	
	int WorldWalls[ 2 ][ 4 ] = {
		{-1, 0, -1, 1}, //left right top bottom
		{0, 1, -1, 1},
	};

	FVector3 MyRadian; //0 == top radian으로 다룸
	FVector3 MyPosition;

public:
	virtual void Update(float DeltaTime) = 0;
	virtual void FixedUpdate(float FixedTime) = 0;
	virtual void HandleWallCollision(const FVector3& WallNormal) = 0;
	virtual void HandleBallCollision(CircleObject& OtherBall) = 0;

	virtual void OnCollision() = 0;
	virtual void Render(const URenderer& Renderer) = 0;
	virtual void Move() = 0 ;
	
	virtual void SetAngle(FVector3 Radian) {
		MyRadian = Radian;
	}

	virtual FVector3 GetAngle() {
		return MyRadian;
	}

	static bool CheckCollision(const CircleObject& A, const CircleObject& B);
};