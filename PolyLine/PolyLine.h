#pragma once
#include "Point.h"

namespace lab4
{
	class Point;

	class PolyLine
	{
	public:
		PolyLine();
		PolyLine(const PolyLine& other);
		~PolyLine();
		bool AddPoint(float x, float y);
		bool AddPoint(const Point* point);
		bool RemovePoint(unsigned int i);
		bool TryGetMinBoundingRectangle(Point* outMin, Point* outMax) const;


		const Point* operator[](unsigned int i) const;
		PolyLine& operator=(const PolyLine& rhs);
		bool operator==(const PolyLine& rhs) const;
		bool operator!=(const PolyLine& rhs) const;


	private:
		static constexpr size_t MAXCAPACITY{ 10 };
		const Point** mPointPointerArray;
		size_t mLineSize;
	};
}