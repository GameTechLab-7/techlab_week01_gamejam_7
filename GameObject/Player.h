#pragma once

#include "GameObject/CircleObject.h"

class Player : public CircleObject {
public:
    Player(EWorld selectedWorld);

	void Update(float DeltaTime);

	void HandleWallCollision(const FVector3& WallNormal);

	void HandleBallCollision(CircleObject& OtherBall);


	void Render(const URenderer& Renderer) const;

	void Move(const float tick);

	void OnDestroy();
};