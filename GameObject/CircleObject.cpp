#include "CircleObject.h"


CircleObject::CircleObject(EWorld SelectedWorld)
    : MyWorld(SelectedWorld)
{
}

void CircleObject::HandleWallCollision(const FVector3& WallNormal)
{
}

void CircleObject::HandleBallCollision(CircleObject* OtherBall)
{
}

void CircleObject::OnHit(FVector3 HitForce , int Damage)
{
	if (HitForce.Length() > 0.0001f)
	{
		Velocity += HitForce;
	}
}


void CircleObject::ResolveOverlap(CircleObject& OtherBall)
{
	const FVector3 Normal = (OtherBall.Location - Location).Normalize();

	float Mass = 1.f;

	const float Penetration = Radius + OtherBall.Radius - (OtherBall.Location - Location).Length();
	const FVector3 Correction = Normal * Penetration / (Mass + 1) * 0.8f;
	Location -= Correction * Mass;
	OtherBall.Location += Correction;
}

FVector3 CircleObject::GetCollisionImpact(CircleObject* HitByObject , CircleObject* HitObject)
{
	const FVector3 Normal = ( HitObject->Location - HitByObject->Location ).Normalize();

	float Scalar = 50.f;
	return Normal * Scalar;
}
