#include <cassert>
#include "Vehicle.h"

namespace assignment2
{
	Vehicle::Vehicle(unsigned int maxPassengersCount)
		: mMaxPassengersCount{ maxPassengersCount }
		, mCurrentPassengersCount{ 0 }
		, mPeopleOnTheVehicle{}
		, mTravelledDistance{0}	
		, mTravelCount{1}
	{

	}

	Vehicle::Vehicle(const Vehicle& rhs)
		: mMaxPassengersCount{rhs.mMaxPassengersCount}
		, mCurrentPassengersCount{rhs.mCurrentPassengersCount}
		, mTravelCount{ rhs.mTravelCount }
		, mTravelledDistance{ rhs.mTravelledDistance }
	{
		for (size_t i{}; i < mCurrentPassengersCount; ++i)
		{
			mPeopleOnTheVehicle[i] = new Person{ *rhs.mPeopleOnTheVehicle[i] };
		}
	}

	Vehicle::~Vehicle()
	{
		for (size_t i{}; i < mCurrentPassengersCount; ++i)
		{
			delete mPeopleOnTheVehicle[i];
		}
	}

	bool Vehicle::AddPassenger(const Person* person)
	{
		assert(person != nullptr);

		if (mCurrentPassengersCount >= mMaxPassengersCount)
		{
			return false;
		}

		else
		{
			mPeopleOnTheVehicle[mCurrentPassengersCount++] = person;
			return true;
		}
	}

	bool Vehicle::RemovePassenger(unsigned int i)
	{
		if (i >= mCurrentPassengersCount)
		{
			return false;
		}

		else
		{
			delete mPeopleOnTheVehicle[i];

			if (i != MAX_COUNT - 1)
			{
				for (size_t j{ i + 1 }; j < mCurrentPassengersCount; ++j)
				{
					mPeopleOnTheVehicle[j - 1] = mPeopleOnTheVehicle[j];
				}

			}

			mCurrentPassengersCount--;
			return true;
		}
	}

	unsigned int Vehicle::GetPassengersCount() const
	{
		return mCurrentPassengersCount;
	}

	unsigned int Vehicle::GetMaxPassengersCount() const
	{
		return mMaxPassengersCount;
	}

	const Person* Vehicle::GetPassenger(unsigned int i) const
	{
		if (i >= mCurrentPassengersCount)
		{
			return nullptr;
		}

		else
		{
			return mPeopleOnTheVehicle[i];
		}
	}

	void Vehicle::MakeVehicleEmpty()
	{
		for (size_t i{}; i < mCurrentPassengersCount; ++i)
		{
			mPeopleOnTheVehicle[i] = nullptr;
		}

		mCurrentPassengersCount = 0;
	}

	size_t Vehicle::GetTravelledDistance() const
	{
		return mTravelledDistance;
	}

	size_t Vehicle::GetTravelCount() const
	{
		return mTravelCount;
	}

	void Vehicle::IncreaseTravelCount()
	{
		mTravelCount++;
	}
}