#include "CircleObject.h"

class CircleObject
{
public:
	FVector3 Location;
	FVector3 Velocity;
	float Radius;

	float Friction = 0.01f;      // 마찰 계수
	float BounceFactor = 0.85f;  // 반발 계수

	bool bApplyGravity = false;
	static float Gravity;

	CircleObject()
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
	{
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
		if (Location.x - Radius < -1.0f)
		{
			Location.x = -1.0f + Radius;
			HandleWallCollision(FVector3(1, 0, 0));
		}
		else if (Location.x + Radius > 1.0f)
		{
			Location.x = 1.0f - Radius;
			HandleWallCollision(FVector3(-1, 0, 0));
		}

		if (Location.y - Radius < -1.0f)
		{
			Location.y = -1.0f + Radius;
			HandleWallCollision(FVector3(0, 1, 0));
		}
		else if (Location.y + Radius > 1.0f)
		{
			Location.y = 1.0f - Radius;
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
		// 충돌 법선 벡터와 상대속도 계산
		const FVector3 Normal = (OtherBall.Location - Location).Normalize();
		const FVector3 RelativeVelocity = OtherBall.Velocity - Velocity;

		const float VelocityAlongNormal = FVector3::DotProduct(RelativeVelocity, Normal);

		// 이미 서로 멀어지고 있는 경우 무시
		if (VelocityAlongNormal > 0) return;

		// 충격량 계산
		const float e = min(BounceFactor, OtherBall.BounceFactor);  // 반발 계수를 둘중 더 작은걸로 설정
		float j = -(1 + e) * VelocityAlongNormal;
		j /= 1 / Mass + 1 / OtherBall.Mass;

		// 속도 업데이트
		const FVector3 Impulse = Normal * j;
		Velocity -= Impulse / Mass;
		OtherBall.Velocity += Impulse / OtherBall.Mass;

		// 마찰 적용
		FVector3 Tangent = RelativeVelocity - Normal * VelocityAlongNormal;
		if (Tangent.LengthSquared() > 0.0001f)  // 탄젠트의 길이가 매우 작으면 건너뛰기
		{
			Tangent = Tangent.Normalize();

			// 탄젠트 충격량 계산
			float JT = -FVector3::DotProduct(RelativeVelocity, Tangent);  // 접선 방향 상대 속도에 기반한 충격량 크기
			JT /= 1 / Mass + 1 / OtherBall.Mass;                               // 두 물체의 유효 질량

			const float MuT = min(Friction, OtherBall.Friction);
			FVector3 FrictionImpulse;
			if (fabsf(JT) < j * MuT)
			{
				// 실제 마찰력 사용
				FrictionImpulse = Tangent * JT;
			}
			else
			{
				// 한계치를 초과시 j * MuT로 제한
				FrictionImpulse = Tangent * -j * MuT;
			}

			// 마찰력 적용
			Velocity -= FrictionImpulse / Mass;
			OtherBall.Velocity += FrictionImpulse / OtherBall.Mass;
		}

		// 겹침 해결
		const float Penetration = Radius + OtherBall.Radius - (OtherBall.Location - Location).Length();
		const FVector3 Correction = Normal * Penetration / (Mass + OtherBall.Mass) * 0.8f;
		Location -= Correction * Mass;
		OtherBall.Location += Correction * OtherBall.Mass;
	}
};