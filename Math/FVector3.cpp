#include "FVector3.h"
#include <cmath>


FVector3::FVector3()
	: x(0), y(0), z(0)
{
}

FVector3::FVector3(float x, float y, float z)
	: x(x), y(y), z(z)
{
}

float FVector3::DotProduct(const FVector3& A, const FVector3& B)
{
	return A.x * B.x + A.y * B.y + A.z * B.z;
}

FVector3 FVector3::CrossProduct(const FVector3& A, const FVector3& B)
{
	return {
		A.y * B.z - A.z * B.y,
		A.z * B.x - A.x * B.z,
		A.x * B.y - A.y * B.x
	};
}

float FVector3::Length() const
{
	return sqrtf(x * x + y * y + z * z);
}

float FVector3::LengthSquared() const
{
	return x * x + y * y + z * z;
}

FVector3 FVector3::Normalize() const
{
	const float VecLength = Length();
	return { x / VecLength, y / VecLength, z / VecLength };
}

float FVector3::Dot(const FVector3& Other) const
{
	return DotProduct(*this, Other);
}

FVector3 FVector3::Cross(const FVector3& Other) const
{
	return CrossProduct(*this, Other);
}

FVector3 FVector3::operator+(const FVector3& Other) const
{
	return { x + Other.x, y + Other.y, z + Other.z };
}

FVector3& FVector3::operator+=(const FVector3& Other)
{
	x += Other.x; y += Other.y; z += Other.z;
	return *this;
}

FVector3 FVector3::operator-(const FVector3& Other) const
{
	return { x - Other.x, y - Other.y, z - Other.z };
}

FVector3& FVector3::operator-=(const FVector3& Other)
{
	x -= Other.x; y -= Other.y; z -= Other.z;
	return *this;
}

FVector3 FVector3::operator*(const FVector3& Other) const
{
	return { x * Other.x, y * Other.y, z * Other.z };
}

FVector3 FVector3::operator*(float Scalar) const
{
	return { x * Scalar, y * Scalar, z * Scalar };
}

FVector3& FVector3::operator*=(float Scalar)
{
	x *= Scalar; y *= Scalar; z *= Scalar;
	return *this;
}

FVector3 FVector3::operator/(const FVector3& Other) const
{
	return { x / Other.x, y / Other.y, z / Other.z };
}

FVector3 FVector3::operator/(float Scalar) const
{
	return { x / Scalar, y / Scalar, z / Scalar };
}

FVector3& FVector3::operator/=(float Scalar)
{
	x /= Scalar; y /= Scalar; z /= Scalar;
	return *this;
}

FVector3 FVector3::operator-() const
{
	return { -x, -y, -z };
}