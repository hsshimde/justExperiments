#include <cassert>
#include "ShimCity.h"

namespace assignment2
{
	ShimCity* ShimCity::GetInstance()
	{
		static ShimCity instance{};

		return &instance;
	}

	ShimCity::ShimCity()
		: mVehicleOnTheCity{}
		, mCurrentVehicleCount{0}
	{
		
	}

	ShimCity::~ShimCity()
	{
		for (size_t i{}; i < mCurrentVehicleCount; ++i)
		{
			delete mVehicleOnTheCity[i];
		}
	}

	void ShimCity::Travel() const
	{
		for (size_t i{}; i < mCurrentVehicleCount; ++i)
		{
			if (mVehicleOnTheCity[i]->GoOnTravel())
			{
				mVehicleOnTheCity[i]->Travel();
			}
		}
	}

	bool ShimCity::AddVehicle(Vehicle* vehicle) 
	{
		assert(vehicle != nullptr);

		if (mCurrentVehicleCount >= MAX_VEHICLE_COUNT)
		{
			return false;
		}

		else
		{
			mVehicleOnTheCity[mCurrentVehicleCount++] = vehicle;
			return true;
		}


	}

	bool ShimCity::RemoveVehicle(unsigned int i)
	{
		if (i >= mCurrentVehicleCount)
		{
			return false;
		}

		else
		{
			delete mVehicleOnTheCity[i];

			if (i != 9)
			{
				for (size_t j{ i + 1 }; j < mCurrentVehicleCount; ++j)
				{
					mVehicleOnTheCity[j - 1] = mVehicleOnTheCity[j];
				}
			}

			mCurrentVehicleCount--;
			return true;

		}
	}

	const Vehicle* ShimCity::GetFurthestTravelled() const
	{
		if (mCurrentVehicleCount == 0)
		{
			return nullptr;
		}

		else
		{
			bool bNoMove{ true };
			size_t highestIndex{};

			for (size_t i{}; i < mCurrentVehicleCount; ++i)
			{

				if (bNoMove && mVehicleOnTheCity[i]->GetTravelledDistance() > 0)
				{
					bNoMove = false;
				}

				if (mVehicleOnTheCity[i]->GetTravelledDistance() > mVehicleOnTheCity[highestIndex]->GetTravelledDistance())
				{
					highestIndex = i;
				}

			}

			if (bNoMove)
			{
				return mVehicleOnTheCity[0];
			}

			else
			{
				return mVehicleOnTheCity[highestIndex];
			}


		}
	}
}