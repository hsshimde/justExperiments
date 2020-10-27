#pragma once
#include "Vehicle.h"
#include "IDrivable.h"

namespace assignment2
{
	class Motorcycle : public Vehicle, public IDrivable
	{
	public:
		Motorcycle();
		virtual ~Motorcycle();

		size_t GetMaxSpeed() const;
		size_t GetDriveSpeed() const;
		bool GoOnTravel();


	};
}