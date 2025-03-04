#include "Monster.h"

class Monster : public CircleObject {

	void Update(float DeltaTime) {
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

	void HandleBallCollision(CircleObject& OtherBall)
	{
		// Monster - Monster
		// if Ball is Monster
		//	 충돌 위치 보정
	}
};