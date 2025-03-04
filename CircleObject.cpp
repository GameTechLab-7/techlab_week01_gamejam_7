#include "CircleObject.h"

class CircleObject
{
public:
	CircleObject(World SelectedWorld)
		: Location{
			static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f) - 1.0f,
			static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f) - 1.0f,
			0.0f
		}
		, Velocity{
			static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f) - 1.0f,
			static_cast<float>(rand()) / (static_cast<float>(RAND_MAX) / 2.0f) - 1.0f,
			0.0f
		}
		, Radius{ static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 0.15f + 0.05f }
		, MyPosition{ FVector3(0, 0, 0) }
		, MyRadian{ FVector3(0, 0, 0)}
	{
		MyWorld = SelectedWorld;
	}

	static bool CheckCollision(const CircleObject& A, const CircleObject& B)
	{
		const float Distance = (A.Location - B.Location).Length();
		return Distance <= (A.Radius + B.Radius);
	}

	void Update(float DeltaTime)
	{
		if (!bApplyGravity)
		{
			Location += Velocity * DeltaTime;
		}

		// Add Velocity
		if (Location.x - Radius < WorldOffset[ MyWorld ][ left ])
		{
			Location.x = WorldOffset[ MyWorld ][ left ] + Radius;
			HandleWallCollision(FVector3(1, 0, 0));
		}
		else if (Location.x + Radius > WorldOffset[ MyWorld ][ right ])
		{
			Location.x = WorldOffset[ MyWorld ][ right ] - Radius;
			HandleWallCollision(FVector3(-1, 0, 0));
		}

		if (Location.y - Radius < WorldOffset[ MyWorld ][ top ])
		{
			Location.y = WorldOffset[ MyWorld ][ top ] + Radius;
			HandleWallCollision(FVector3(0, 1, 0));
		}
		else if (Location.y + Radius > WorldOffset[ MyWorld ][ bottom ])
		{
			Location.y = WorldOffset[ MyWorld ][ bottom ] - Radius;
			HandleWallCollision(FVector3(0, -1, 0));
		}
	}

	void FixedUpdate(float FixedTime)
	{
		if (!bApplyGravity) return;

		Location += Velocity * FixedTime;
		Velocity.y += Gravity * FixedTime;
	}

	void Render(const URenderer& Renderer) const
	{
		Renderer.UpdateConstant(Location, Radius);
	}

	void HandleWallCollision(const FVector3& WallNormal)
	{
		// 속도를 벽면에 수직인 성분과 평행한 성분으로 분해
		FVector3 VelocityNormal = WallNormal * FVector3::DotProduct(Velocity, WallNormal);
		const FVector3 VelocityTangent = Velocity - VelocityNormal;

		// 수직 속도 성분에 반발 계수를 적용하여 반사
		VelocityNormal = -VelocityNormal * BounceFactor;

		// 반사된 수직 속도와 마찰이 적용된 평행 속도를 합하여 최종 속도 계산
		Velocity = VelocityNormal + VelocityTangent * (1.0f - Friction);
	}

	void HandleBallCollision(CircleObject& OtherBall)
	{

	}
};