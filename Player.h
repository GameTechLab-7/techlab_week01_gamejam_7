#pragma once

#include "CircleObject.h"

class Player : public CircleObject {
public:
	Player(World selectedWorld) : CircleObject(selectedWorld) {
		Radius = 0.5;
	};

	void Update(float DeltaTime);

	void HandleWallCollision(const FVector3& WallNormal);

	void HandleBallCollision(CircleObject& OtherBall);


	void Render(const URenderer& Renderer) const;

	void Move(const float tick);

	void OnDestroy();
};