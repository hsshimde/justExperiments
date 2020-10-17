#pragma once
#include "Trucks.h"	
namespace codingpractice
{
	class Truck;

	class Bridge
	{
	public:
		static Bridge* GetBridge(const size_t weightCapacity, const size_t bridgeLength, const size_t maxTruckCount);
		const Truck*  GetFrontTruck() const;
		bool PossibleToHandleAnotherTruck(size_t truckWeight) const;
		void AddTruck(Truck* truck);
		bool RemoveTruck(const size_t currentTime);
		size_t GetCurrentTrucksWeightSum() const;
		size_t GetCrossedTruckCount() const;
	
		

		

	private:

		Bridge(size_t weightCapacity, size_t bridgeLength, size_t maxTruckCount);
		~Bridge();
		Bridge(const Bridge& rhs) = delete;

		size_t mMaxTruckCount;
		size_t mWeightCapacity;
		size_t mBridgeLength;
		size_t mCurrentFrontTruckIndex;
		size_t mTrucksCount;

		Truck** mTrucksOnTheBridge;
		


	};
}