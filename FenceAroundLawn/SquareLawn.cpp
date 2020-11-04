
#include "SquareLawn.h"
#include "IFencable.h"


namespace lab5
{
	SquareLawn::SquareLawn(size_t width)
		: RectangleLawn{ width, width }
	{

	}

	SquareLawn::SquareLawn(const SquareLawn& rhs)
		: RectangleLawn{ rhs.mWidth, rhs.mHeight }
	{

	}

	SquareLawn::~SquareLawn()
	{

	}

	SquareLawn& SquareLawn::operator=(const SquareLawn& rhs)
	{
		RectangleLawn::operator=(rhs);
		return *this;
	}



}