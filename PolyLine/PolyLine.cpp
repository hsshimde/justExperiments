#include <cstring>
#include <cmath>
#include <cfloat>
#include "PolyLine.h"

namespace lab4
{
	PolyLine::PolyLine()
		: mLineSize{ 0 }
		, mPointPointerArray{ }
	{
		mPointPointerArray = new Point * [MAXCAPACITY];
	}

	PolyLine::PolyLine(const PolyLine& other)
		: mLineSize{ other.mLineSize }
	{
		for (size_t i{}; i < mLineSize; ++i)
		{
			mPointPointerArray[i] = new Point{ other.mPointPointerArray[i]->mX, other.mPointPointerArray[i]->mY };
		}
	}

	PolyLine& PolyLine::operator=(const PolyLine& rhs)
	{

		if (*this == rhs)
		{
			return *this;
		}

		else
		{
			for (size_t i{}; i < mLineSize; ++i)
			{
				delete mPointPointerArray[i];
				mPointPointerArray[i] = new Point{ rhs.mPointPointerArray[i]->mX, rhs.mPointPointerArray[i]->mY };
			}

			return *this;
		}


	}

	PolyLine::~PolyLine()
	{
		for (size_t i{}; i < mLineSize; ++i)
		{
			delete mPointPointerArray[i];
		}


	}

	bool PolyLine::AddPoint(float x, float y)
	{
		if (mLineSize >= MAXCAPACITY)
		{
			return false;
		}

		else
		{
			mPointPointerArray[mLineSize] = new Point{ x, y };
			++mLineSize;

			return true;
		}
	}

	bool PolyLine::AddPoint(const Point* point)
	{
		if (point == nullptr)
		{
			return false;
		}

		if (mLineSize >= MAXCAPACITY)
		{
			return false;
		}

		else
		{
			mPointPointerArray[mLineSize++] = point;
			return true;
		}
	}



	bool PolyLine::RemovePoint(unsigned int i)
	{
		if (i >= mLineSize)
		{
			return false;
		}

		else
		{
			delete mPointPointerArray[i];


			if (i != 9)
			{
				for (size_t j{ i + 1 }; j < mLineSize; ++j)
				{
					mPointPointerArray[j - 1] = mPointPointerArray[j];
				}
			}
			--mLineSize;

			return true;
		}


	}

	bool PolyLine::TryGetMinBoundingRectangle(Point* outMin, Point* outMax) const
	{
		if (mLineSize == 0)
		{
			return false;
		}

		else
		{
			float minForX{ mPointPointerArray[0]->GetX() };
			float maxForX{ mPointPointerArray[0]->GetX() };
			float minForY{ mPointPointerArray[0]->GetY() };
			float maxForY{ mPointPointerArray[0]->GetY() };



			for (size_t j{ 1 }; j < mLineSize; ++j)
			{
				if (mPointPointerArray[j]->mX > maxForX)
				{
					maxForX = mPointPointerArray[j]->mX;
				}


				if (mPointPointerArray[j]->mX < minForX)
				{
					minForX = mPointPointerArray[j]->mX;
				}


				if (mPointPointerArray[j]->mY > maxForY)
				{
					maxForY = mPointPointerArray[j]->mY;
				}


				if (mPointPointerArray[j]->mY < minForY)
				{
					minForY = mPointPointerArray[j]->mY;
				}


			}

			outMin->mX = minForX;
			outMin->mY = minForY;

			outMax->mX = maxForX;
			outMax->mY = maxForY;

			return true;

		}
	}

	const Point* PolyLine::operator[](unsigned int i) const
	{
		if (i >= mLineSize)
		{
			return nullptr;
		}

		else
		{
			return mPointPointerArray[i];
		}
	}

	bool PolyLine::operator==(const PolyLine& rhs) const
	{
		if (mLineSize != rhs.mLineSize)
		{
			return false;
		}

		for (size_t i{}; i < mLineSize; ++i)
		{
			if (*mPointPointerArray[i] != *rhs.mPointPointerArray[i])
			{
				return false;
			}
		}

		return true;
	}

	bool PolyLine::operator!=(const PolyLine& rhs) const
	{
		return !(*this == rhs);
	}

}