#pragma once
#include <EASTL/vector.h>

struct Matrix4D
{
	float m[4][4] = { 0.0f };
};

//struct Matrix4D
//{
//	float m[3][3] = { 0.0f }; 
//};

class Vector3D final
{
public:
	Vector3D(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f);
	~Vector3D();

	void Multiply(float value);
	void Divide(float value);
	void Normalize();

	float GetSize() const;

	Vector3D operator+(const Vector3D& rhs) const;
	Vector3D operator-(const Vector3D& rhs) const;
	Vector3D operator*(float value) const;
	Vector3D operator/(float value) const;

	void operator+=(const Vector3D& rhs);
	void operator-=(const Vector3D& rhs);
	Vector3D GetCrossProduct(const Vector3D& rhs) const;
	float GetDotProduct(const Vector3D& rhs) const;
	//Vector3D MakeProjection(const Matrix4D& mat) const;

	void AddScreenOffset(const float offset);
	float GetPlaneEquationValue(const Vector3D& normal, const Vector3D& passingPoint) const;
	Vector3D GetIntersectPlaneVector(const Vector3D& normal, const Vector3D& passingPoint, const Vector3D& endPoint) const;


	//Vector3D MultiplyMatrix(const Matrix4D& mat) const;
	Vector3D MultiplyMatrix(const Matrix4D& mat) const;
public:
	float mfX;
	float mfY;
	float mfZ;
	float mfW;
};

struct Triangle
{
	Vector3D Point[3];

	wchar_t symbol;
	short color;
};


struct Mesh
{
	eastl::vector<Triangle> triangles;
};
