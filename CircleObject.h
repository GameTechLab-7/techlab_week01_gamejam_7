#pragma once
#include <d3d11.h>
#include "FVector3.h"
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
	float Radius = 0.f;

	World MyWorld;
	
	int WorldWalls[ 2 ][ 4 ] = {
		{-1, 0, -1, 1}, //left right top bottom
		{0, 1, -1, 1},
	};

	FVector3 MyRadian = FVector3(); //0 == top radian으로 다룸
	FVector3 MyPosition = FVector3();

public:
	CircleObject(World SelectedWorld);

	//virtual void Update(float DeltaTime) = 0;
	//virtual void FixedUpdate(float FixedTime) = 0;
	virtual void HandleWallCollision(const FVector3& WallNormal) = 0;
	virtual void HandleBallCollision(CircleObject& OtherBall) = 0;

	virtual void Render(const URenderer& Renderer) const = 0;
	
	virtual void SetAngle(FVector3 Radian) {
		MyRadian = Radian;
	}

	virtual FVector3 GetAngle() {
		return MyRadian;
	}
	virtual void Move(const float tick) = 0 ;
	virtual void OnDestroy() = 0;	// CircleObject에 의해 부가적으로 발생한 메모리만 삭제, CircleObject 객체는 ObjectManager에 의해 삭제.
};