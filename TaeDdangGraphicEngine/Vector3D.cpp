#include <cassert>
#include <cmath>

#include "Vector3D.h"


Vector3D::Vector3D(float x, float y, float z,float w)
	: mfX( x )
	, mfY( y )
	, mfZ( z ) 
	, mfW( w )
{

}

Vector3D::~Vector3D()
{

}



void Vector3D::Multiply(float value)
{
	mfX *= value;
	mfY *= value;
	mfZ *= value;
	return;
}

void Vector3D::Divide(float value)
{
	mfX /= value;
	mfY /= value;
	mfZ /= value;
	return;
}

void Vector3D::Normalize()
{
	float length = GetSize();
	assert(length != 0.0f);
	if (length != 1.00f)
	{
		Divide(length);
	}
	return;
}

float Vector3D::GetSize() const
{
	return std::sqrtf(mfX * mfX + mfY * mfY + mfZ * mfZ);
}


Vector3D Vector3D::GetCrossProduct(const Vector3D& rhs) const
{
	Vector3D result{};
	result.mfX = mfY * rhs.mfZ - mfZ * rhs.mfY;
	result.mfY = -(mfX * rhs.mfZ - mfZ * rhs.mfX);
	result.mfZ = mfX * rhs.mfY - rhs.mfX * mfY;

	return result;
}

float Vector3D::GetDotProduct(const Vector3D& rhs) const
{
	return (mfX * rhs.mfX + mfY * rhs.mfY + mfZ * rhs.mfZ);
}

Vector3D Vector3D::operator+(const Vector3D& rhs) const
{
	Vector3D result{};

	result.mfX = mfX + rhs.mfX;
	result.mfY = mfY + rhs.mfY;
	result.mfZ = mfZ + rhs.mfZ;
	return result;
}

Vector3D Vector3D::operator-(const Vector3D& rhs) const
{
	Vector3D result{};

	result.mfX = mfX - rhs.mfX;
	result.mfY = mfY - rhs.mfY;
	result.mfZ = mfZ - rhs.mfZ;
	return result;
}

Vector3D Vector3D::operator*(float value) const
{
	Vector3D result{};

	result.mfX = mfX * value;
	result.mfY = mfY * value;
	result.mfZ = mfZ * value;
	return result;
}
Vector3D Vector3D::MultiplyMatrix(const Matrix4D& mat) const
{
	float vectorElement[4];

	vectorElement[0] = mfX * mat.m[0][0] + mfY * mat.m[0][1] + mfZ * mat.m[0][2] + mfW * mat.m[0][3];
	vectorElement[1] = mfX * mat.m[1][0] + mfY * mat.m[1][1] + mfZ * mat.m[1][2] + mfW * mat.m[1][3];
	vectorElement[2] = mfX * mat.m[2][0] + mfY * mat.m[2][1] + mfZ * mat.m[2][2] + mfW * mat.m[2][3];
	vectorElement[3] = mfX * mat.m[3][0] + mfY * mat.m[3][1] + mfZ * mat.m[3][2] + mfW * mat.m[3][3];
	
	return Vector3D{ vectorElement[0],vectorElement[1], vectorElement[2],vectorElement[3] };

}
Vector3D Vector3D::MultiplyMatrix(const Matrix3D& mat) const
{
	float vectorElement[3];

	vectorElement[0] = mfX * mat.m[0][0] + mfY * mat.m[0][1] + mfZ * mat.m[0][2] ;
	vectorElement[1] = mfX * mat.m[1][0] + mfY * mat.m[1][1] + mfZ * mat.m[1][2] ;
	vectorElement[2] = mfX * mat.m[2][0] + mfY * mat.m[2][1] + mfZ * mat.m[2][2] ;
	//vectorElement[3] = mfX * mat.m[3][0] + mfY * mat.m[3][1] + mfZ * mat.m[3][2] + mfW * mat.m[3][3];

	return Vector3D{ vectorElement[0],vectorElement[1], vectorElement[2],1.0f};

}

Vector3D Vector3D::MakeProjection(const Matrix4D& mat) const
{
	
	float vectorElement[4];

	vectorElement[0] = mfX * mat.m[0][0] + mfY * mat.m[0][1] + mfZ * mat.m[0][2] + mfW * mat.m[0][3];
	vectorElement[1] = mfX * mat.m[1][0] + mfY * mat.m[1][1] + mfZ * mat.m[1][2] + mfW * mat.m[1][3];
	vectorElement[2] = mfX * mat.m[2][0] + mfY * mat.m[2][1] + mfZ * mat.m[2][2] + mfW * mat.m[2][3];
	vectorElement[3] = mfX * mat.m[3][0] + mfY * mat.m[3][1] + mfZ * mat.m[3][2] + mfW * mat.m[3][3];
	
	if (vectorElement[3] != 0.0f)
	{
		vectorElement[0] /= vectorElement[3];
		vectorElement[1] /= vectorElement[3];
	}
	return Vector3D{ vectorElement[0], vectorElement[1], 1.0f };

}