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

		if (Location.y - Radius < WorldWalls[ MyWorld ][ top ])
		{
			Location.y = WorldWalls[ MyWorld ][ top ] + Radius;
		}
		else if (Location.y + Radius > WorldWalls[ MyWorld ][ bottom ])
		{
			Location.y = WorldWalls[ MyWorld ][ bottom ] - Radius;
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