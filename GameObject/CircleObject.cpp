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

void CircleObject::OnHit()
{
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
