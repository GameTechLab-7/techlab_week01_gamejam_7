#include "GameObject/Player.h"


	// 문제 1. 벽 겹침 보정을 언제 어디서 해주냐
	

	// Move 이후? 뭐 어디서? 
	
	// 이동 후 겹침 보정 (Monster, Player에 대해)
	void Player::Update(float DeltaTime) {
		// 벽
		if (Location.x - Radius < WorldWalls[ MyWorld ][ left ])
		{
			Location.x = WorldWalls[ MyWorld ][ left ] + Radius;
		}
		else if (Location.x + Radius > WorldWalls[ MyWorld ][ right ])
		{
			Location.x = WorldWalls[ MyWorld ][ right ] - Radius;
		}

// 이동 후 겹침 보정 (Monster, Player에 대해)
{
    // 벽
    if (Location.x - Radius < WorldWalls[MyWorld][Left])
    {
        Location.x = WorldWalls[MyWorld][Left] + Radius;
    }
    else if (Location.x + Radius > WorldWalls[MyWorld][Right])
    {
        Location.x = WorldWalls[MyWorld][Right] - Radius;
    }

    if (Location.y - Radius < WorldWalls[MyWorld][Top])
    {
        Location.y = WorldWalls[MyWorld][Top] + Radius;
    }
    else if (Location.y + Radius > WorldWalls[MyWorld][Bottom])
    {
        Location.y = WorldWalls[MyWorld][Bottom] - Radius;
    }
}

	void Player::HandleWallCollision(const FVector3& WallNormal) {

	}

	void Player::HandleBallCollision(CircleObject& OtherBall) {
		// Monster -> Player
		// Player 넉백 -> velocity
		// Player Damage 
		// Player 무적 
	}


	void Player::Render(const URenderer& Renderer) const {
		Renderer.UpdateConstant(Location , Radius);
	}

	void Player::Move(const float tick) {
		Location += Velocity * tick;
	}


	void Player::OnDestroy() {

	}