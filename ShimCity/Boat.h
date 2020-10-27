#pragma once

#include "Boatplane.h"
#include "Vehicle.h"
#include "ISailable.h"

namespace assignment2
{
	class Airplane;

	class Boat : public Vehicle, public ISailable
	{
	public:
		Boat(unsigned int maxPassengersCount);
		~Boat();

		Boatplane operator+(Airplane& plane);
		virtual size_t GetMaxSpeed() const;
		virtual size_t GetSailSpeed() const;
		virtual bool GoOnTravel();

	};
}