#pragma once
#include "PolyLine.h"

namespace lab4
{
	class Point
	{
		friend class PolyLine;

	public:
		Point();
		Point(float x, float y);
		~Point();

		Point operator+(const Point& other) const;
		Point operator-(const Point& other) const;
		Point& operator=(const Point& other);
		float Dot(const Point& other) const;
		Point operator*(float operand) const;
		friend Point operator*(float operand, const Point& rhs);
		float GetX() const;
		float GetY() const;
		bool operator==(const Point& rhs) const;
		bool operator!=(const Point& rhs) const;



	private:
		float mX;
		float mY;
	};
}