#pragma once

#include "Vehicle.h"

namespace assignment2
{
	class ShimCity
	{
	public:
		static ShimCity* GetInstance();
		void Travel() const;
		bool AddVehicle(Vehicle* vehicle);
		bool RemoveVehicle(unsigned int i);
		const Vehicle* GetFurthestTravelled() const;

	private:
		ShimCity();
		~ShimCity();

		static constexpr size_t MAX_VEHICLE_COUNT{ 10 };
		Vehicle* mVehicleOnTheCity[MAX_VEHICLE_COUNT];
		size_t mCurrentVehicleCount;

		
	};
}