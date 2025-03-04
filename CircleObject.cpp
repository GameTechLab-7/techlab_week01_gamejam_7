#include "CircleObject.h"

class CircleObject
{
public:
	FVector3 Location;
	FVector3 Velocity;
	float Radius;

	float Friction = 0.01f;      // ���� ���
	float BounceFactor = 0.85f;  // �ݹ� ���

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
		// �ӵ��� ���鿡 ������ ���а� ������ �������� ����
		FVector3 VelocityNormal = WallNormal * FVector3::DotProduct(Velocity, WallNormal);
		const FVector3 VelocityTangent = Velocity - VelocityNormal;

		// ���� �ӵ� ���п� �ݹ� ����� �����Ͽ� �ݻ�
		VelocityNormal = -VelocityNormal * BounceFactor;

		// �ݻ�� ���� �ӵ��� ������ ����� ���� �ӵ��� ���Ͽ� ���� �ӵ� ���
		Velocity = VelocityNormal + VelocityTangent * (1.0f - Friction);
	}

	void HandleBallCollision(CircleObject& OtherBall)
	{
		// �浹 ���� ���Ϳ� ���ӵ� ���
		const FVector3 Normal = (OtherBall.Location - Location).Normalize();
		const FVector3 RelativeVelocity = OtherBall.Velocity - Velocity;

		const float VelocityAlongNormal = FVector3::DotProduct(RelativeVelocity, Normal);

		// �̹� ���� �־����� �ִ� ��� ����
		if (VelocityAlongNormal > 0) return;

		// ��ݷ� ���
		const float e = min(BounceFactor, OtherBall.BounceFactor);  // �ݹ� ����� ���� �� �����ɷ� ����
		float j = -(1 + e) * VelocityAlongNormal;
		j /= 1 / Mass + 1 / OtherBall.Mass;

		// �ӵ� ������Ʈ
		const FVector3 Impulse = Normal * j;
		Velocity -= Impulse / Mass;
		OtherBall.Velocity += Impulse / OtherBall.Mass;

		// ���� ����
		FVector3 Tangent = RelativeVelocity - Normal * VelocityAlongNormal;
		if (Tangent.LengthSquared() > 0.0001f)  // ź��Ʈ�� ���̰� �ſ� ������ �ǳʶٱ�
		{
			Tangent = Tangent.Normalize();

			// ź��Ʈ ��ݷ� ���
			float JT = -FVector3::DotProduct(RelativeVelocity, Tangent);  // ���� ���� ��� �ӵ��� ����� ��ݷ� ũ��
			JT /= 1 / Mass + 1 / OtherBall.Mass;                               // �� ��ü�� ��ȿ ����

			const float MuT = min(Friction, OtherBall.Friction);
			FVector3 FrictionImpulse;
			if (fabsf(JT) < j * MuT)
			{
				// ���� ������ ���
				FrictionImpulse = Tangent * JT;
			}
			else
			{
				// �Ѱ�ġ�� �ʰ��� j * MuT�� ����
				FrictionImpulse = Tangent * -j * MuT;
			}

			// ������ ����
			Velocity -= FrictionImpulse / Mass;
			OtherBall.Velocity += FrictionImpulse / OtherBall.Mass;
		}

		// ��ħ �ذ�
		const float Penetration = Radius + OtherBall.Radius - (OtherBall.Location - Location).Length();
		const FVector3 Correction = Normal * Penetration / (Mass + OtherBall.Mass) * 0.8f;
		Location -= Correction * Mass;
		OtherBall.Location += Correction * OtherBall.Mass;
	}
};