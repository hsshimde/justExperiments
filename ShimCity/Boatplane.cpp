#include "Boatplane.h"

namespace assignment2
{
	Boatplane::Boatplane(unsigned int maxPassengersCount)
		: Vehicle{maxPassengersCount}
	{

	}

	Boatplane::~Boatplane()
	{

	}

	size_t Boatplane::GetFlySpeed() const
	{

	}

	size_t Boatplane::GetSailSpeed() const
	{

	}

	size_t Boatplane::GetMaxSpeed() const
	{
		size_t sailSpeed{ GetSailSpeed() };
		size_t flySpeed{ GetFlySpeed() };

		return (sailSpeed > flySpeed) ? sailSpeed : flySpeed;
	}

	bool Boatplane::GoOnTravel()
	{
		size_t travelCount{ GetTravelCount() };
		IncreaseTravelCount();

		if (travelCount % 4 == 1)
		{
			return true;
		}

		else
		{
			return false;
		}
	}
}