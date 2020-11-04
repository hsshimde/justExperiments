#include <cmath>
#include <cassert>

#include "EquilateralTriangleLawn.h"
#include "IFencable.h"

namespace lab5
{

	EquilateralTriangleLawn::EquilateralTriangleLawn(size_t side)
		: mSide{ side }
	{

	}

	EquilateralTriangleLawn::EquilateralTriangleLawn(const EquilateralTriangleLawn& rhs)
		: mSide{ rhs.mSide }
	{

	}

	EquilateralTriangleLawn::~EquilateralTriangleLawn()
	{

	}

	EquilateralTriangleLawn& EquilateralTriangleLawn::operator=(const EquilateralTriangleLawn& rhs)
	{
		mSide = rhs.mSide;
		return *this;
	}

	size_t EquilateralTriangleLawn::GetArea() const
	{
		return static_cast<size_t>(std::floor(std::sqrt(3) * mSide * mSide / 4 + 0.5));
	}

	size_t EquilateralTriangleLawn::GetFencePrice(eFenceType fenceType) const
	{
		size_t fencePricePerMeter{};


		/*RED_CEDAR,
			SPRUCE*/
		switch (fenceType)
		{
		case eFenceType::RED_CEDAR:
			fencePricePerMeter = 6;
			break;

		case eFenceType::SPRUCE:
			fencePricePerMeter = 7;
			break;

		default:
			assert((false, "unknown type"));
			break;

		}

		return 3 * fencePricePerMeter * mSide;
	}

	size_t EquilateralTriangleLawn::GetMinimumFencesCount() const
	{
		return 3 * 4 * mSide;
	}



}