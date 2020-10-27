#pragma once

#include "Vehicle.h"
#include "IFlyable.h"
#include "IDrivable.h"
#include "Boatplane.h"

namespace assignment2
{
	class Boat;

	class Airplane : public Vehicle, public IFlyable
	{
	public:
		Airplane(unsigned int maxPassengersCount);
		~Airplane();

		virtual size_t GetMaxSpeed() const;
		virtual size_t GetDriveSpeed() const;
		virtual size_t GetFlySpeed() const;
		virtual bool GoOnTravel();


		Boatplane operator+(Boat& boat);
	};
}