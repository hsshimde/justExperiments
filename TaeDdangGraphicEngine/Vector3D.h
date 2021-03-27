#pragma once
#include <vector>

struct Matrix4D
{
	float m[4][4] = { 0.0f };
};

struct Matrix3D
{
	float m[3][3] = { 0.0f }; 
};

class Vector3D final
{
public:
	Vector3D(float x = 0.0f, float y = 0.0f, float z = 0.0f,float w = 1.0f);
	~Vector3D();
	
	void Multiply(float value);
	void Divide(float value);
	void Normalize();
	
	float GetSize() const;

	Vector3D operator+(const Vector3D& rhs) const;
	Vector3D operator-(const Vector3D& rhs) const;
	Vector3D operator*(float value) const;
	Vector3D GetCrossProduct(const Vector3D& rhs) const;
	float GetDotProduct(const Vector3D& rhs) const;
	Vector3D MakeProjection(const Matrix4D& mat) const;


	Vector3D MultiplyMatrix(const Matrix3D& mat) const;
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
	std::vector<Triangle> triangles;
};
