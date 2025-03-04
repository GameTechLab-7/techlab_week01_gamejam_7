#pragma once

struct FVector3 {
	float x, y, z;
	FVector3();
	FVector3(float x, float y, float z);

	static float DotProduct(const FVector3& A, const FVector3& B);

	static FVector3 CrossProduct(const FVector3& A, const FVector3& B);

	float Length() const;

	float LengthSquared() const;

	FVector3 Normalize() const;

	float Dot(const FVector3& Other) const;

	FVector3 Cross(const FVector3& Other) const;

	FVector3 operator+(const FVector3& Other) const;

	FVector3& operator+=(const FVector3& Other);

	FVector3 operator-(const FVector3& Other) const;

	FVector3& operator-=(const FVector3& Other);

	FVector3 operator*(const FVector3& Other) const;

	FVector3 operator*(float Scalar) const;

	FVector3& operator*=(float Scalar);

	FVector3 operator/(const FVector3& Other) const;

	FVector3 operator/(float Scalar) const;

	FVector3& operator/=(float Scalar);

	FVector3 operator-() const;
};