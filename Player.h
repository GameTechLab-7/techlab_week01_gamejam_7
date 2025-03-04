#pragma once

#include "CircleObject.h"

class Player : public CircleObject {
public:
	Player(EWorld selectedWorld) : CircleObject(selectedWorld) {
		Radius = 0.3;
		float x = rand() % 1 - MyWorld;
		float y = rand() % 2 - 1;
		Location = FVector3(x, y, 0);
		Velocity = FVector3(x, y, 0);
	};

	void Update(float DeltaTime);

	void HandleWallCollision(const FVector3& WallNormal);

	void HandleBallCollision(CircleObject& OtherBall);


	void Render(const URenderer& Renderer) const;

	void Move(const float tick);

	void OnDestroy();
};