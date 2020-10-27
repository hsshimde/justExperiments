#include "Boat.h"
#include "Airplane.h"

namespace assignment2
{
	Boat::Boat(unsigned int maxPassengersCount)
		: Vehicle{ maxPassengersCount }
	{

	}

	Boat::~Boat()
	{
	}

	Boatplane Boat::operator+(Airplane& plane)
	{
		return plane + *this;
	}

	size_t Boat::GetMaxSpeed() const
	{
		return GetSailSpeed();
	}

	size_t Boat::GetSailSpeed() const
	{

	}

	bool Boat::GoOnTravel()
	{
		size_t travelCount{ GetTravelCount() };
		IncreaseTravelCount();

		if (travelCount % 3 == 0)
		{
			return false;
		}

		else
		{
			return true;
		}
	}
}