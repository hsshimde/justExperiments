
#include "CircleLawn.h"


namespace lab5
{
	CircleLawn::CircleLawn(size_t radius)
		: mRadius{ radius }
	{

	}

	CircleLawn::CircleLawn(const CircleLawn& rhs)
		: mRadius{ rhs.mRadius }
	{

	}

	CircleLawn::~CircleLawn()
	{

	}


	CircleLawn& CircleLawn::operator=(const CircleLawn& rhs)
	{
		mRadius = rhs.mRadius;
		return *this;
	}

	size_t CircleLawn::GetArea() const
	{
		return static_cast<size_t>(std::floor(3.14 * mRadius * mRadius + 0.5));
	}
}