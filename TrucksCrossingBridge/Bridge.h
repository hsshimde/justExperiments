#pragma once
#include "Trucks.h"	
namespace codingpractice
{
	class Truck;

	class Bridge
	{
	public:
		static Bridge* GetBridge(size_t weightCapacity, size_t bridgeLength,size_t maxTruckCount);
		const Truck*  GetFrontTruck() const;
		bool PossibleToHandleAnotherTruck(size_t truckWeight) const;
		void AddTruck(Truck* truck);
		bool RemoveTruck(size_t currentTime);
		size_t GetCurrentTrucksWeightSum() const;
		size_t GetTruckCrossedCount() const;

		

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