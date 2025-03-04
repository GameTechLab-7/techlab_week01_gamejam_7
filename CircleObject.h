#pragma once
#include "FVector3.h"
#include <d3d11.h>
#include "URenderer.h"


class CircleObject {
public:
	virtual void Update(float DeltaTime) = 0;
	virtual void FixedUpdate(float FixedTime) = 0;
	virtual void HandleWallCollision(const FVector3& WallNormal) = 0;
	virtual void HandleBallCollision(CircleObject& OtherBall) = 0;

	virtual void OnCollision() = 0;
	virtual void Render(const URenderer& Renderer) = 0;
	virtual void Move() = 0 ;
	
	static bool CheckCollision(const CircleObject& A, const CircleObject& B);
};