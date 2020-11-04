#include <cmath>
#include <cassert>

#include "RectangleLawn.h"
#include "IFencable.h"


namespace lab5
{
	RectangleLawn::RectangleLawn(size_t width, size_t height)
		: mWidth{ width }
		, mHeight{ height }
	{

	}

	RectangleLawn::RectangleLawn(const RectangleLawn& rhs)
		: mWidth{ rhs.mWidth }
		, mHeight{ rhs.mHeight }
	{

	}


	RectangleLawn::~RectangleLawn()
	{

	}


	size_t RectangleLawn::GetMinimumFencesCount() const
	{
		return 4 * 2 * (mWidth + mHeight);
	}

	size_t RectangleLawn::GetFencePrice(eFenceType fenceType) const
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

		size_t wholeFenceLength{ (mWidth + mHeight) * 2 };

		return static_cast<size_t>(std::floor((static_cast<double>(wholeFenceLength) * static_cast<double>(fencePricePerMeter) + 0.5)));

	}

	RectangleLawn& RectangleLawn::operator=(const RectangleLawn& rhs)
	{
		mWidth = rhs.mWidth;
		mHeight = rhs.mHeight;

		return *this;
	}

	size_t RectangleLawn::GetArea() const
	{
		return mWidth * mHeight;
	}


}