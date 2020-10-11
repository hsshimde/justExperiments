#include <iostream>

#include "Bridge.h"

namespace codingpractice
{
	Bridge* Bridge::GetBridge(size_t weightCapacity, size_t bridgeLength, size_t maxTruckCount)
	{
		static Bridge br{ weightCapacity, bridgeLength, maxTruckCount };

		return &br;

	}
	/*size_t mMaxTruckCount;
	size_t mWeightCapacity;
	size_t mBridgeLength;
	size_t mCurrentTrucksWeightSum;
	size_t mCurrentFrontTruckIndex;
	size_t mTrucksCount;
	size_t mTruckCrossedCount;

	Truck** mTrucksOnTheBridge;*/


	Bridge::Bridge(size_t weightCapacity, size_t bridgeLength, size_t maxTruckCount)
		: mMaxTruckCount{ maxTruckCount }
		, mWeightCapacity{ weightCapacity }
		, mBridgeLength{ bridgeLength }
		, mCurrentFrontTruckIndex{ 0 }
		, mTrucksCount{ 0 }
	{
		mTrucksOnTheBridge = new Truck * [maxTruckCount];
	}

	Bridge::~Bridge()
	{
		for (size_t i{}; i < mTrucksCount; ++i)
		{
			delete mTrucksOnTheBridge[i];
		}

		delete[] mTrucksOnTheBridge;

	}

	const Truck* Bridge::GetFrontTruck() const
	{
		return mTrucksOnTheBridge[mCurrentFrontTruckIndex];
	}

	bool Bridge::PossibleToHandleAnotherTruck(size_t truckWeight) const
	{
		if (GetCurrentTrucksWeightSum() + truckWeight <= mWeightCapacity)
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	void Bridge::AddTruck(Truck* truck)
	{
		mTrucksOnTheBridge[mTrucksCount++] = truck;
	}

	bool Bridge::RemoveTruck(size_t currentTime)
	{
		if (mTrucksCount == 0 || mTrucksCount == mCurrentFrontTruckIndex)
		{
			return false;
		}

		else if (currentTime - mTrucksOnTheBridge[mCurrentFrontTruckIndex]->GetTime() >= mBridgeLength)
		{
			mCurrentFrontTruckIndex++;
			return true;
		}

		else
		{
			return false;
		}
	}

	size_t Bridge::GetCurrentTrucksWeightSum() const
	{
		size_t totalWeight{};

		for (size_t i{ mCurrentFrontTruckIndex }; i < mTrucksCount; ++i)
		{
			totalWeight += mTrucksOnTheBridge[i]->GetWeight();
		}

		return totalWeight;
	}


	size_t Bridge::GetCrossedTruckCount() const
	{
		return mCurrentFrontTruckIndex;
	}

}