#include "Point.h"

namespace lab4
{
	Point::Point()
		: mX{ 0.0f }
		, mY{ 0.0f }
	{

	}

	Point::Point(float x, float y)
		: mX{ x }
		, mY{ y }
	{

	}

	Point::~Point()
	{
	}

	Point Point::operator+(const Point& other) const
	{
		return Point{ mX + other.mX, mY + other.mY };
	}

	Point Point::operator-(const Point& other) const
	{
		return Point{ mX - other.mX, mY - other.mY };
	}

	Point& Point::operator=(const Point& other)
	{
		mX = other.mX;
		mY = other.mY;

		return *this;
	}

	float Point::Dot(const Point& other) const
	{
		return  mX * other.mX + mY * other.mY;
	}

	Point Point::operator*(float operand) const
	{
		return Point{ mX * operand, mY * operand };
	}

	Point operator*(float operand, const Point& rhs)
	{
		return rhs * operand;
	}

	float Point::GetX() const
	{
		return mX;
	}

	float Point::GetY() const
	{
		return mY;
	}

	bool Point::operator==(const Point& rhs) const
	{
		return mX == rhs.mX && mY == rhs.mY;
	}

	bool Point::operator!=(const Point& rhs) const
	{
		return !(*this == rhs);
	}


}