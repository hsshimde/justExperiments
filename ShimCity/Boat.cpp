#include <string>
#include "Boat.h"
#include "Airplane.h"

namespace assignment2
{
	Boat::Boat(unsigned int maxPassengersCount)
		: Vehicle{ maxPassengersCount }
	{

	}

	Boat::Boat(const Boat& rhs)
		: Vehicle{ rhs }
	{

	}

	Boat& Boat::operator=(const Boat& rhs)
	{
		Vehicle::operator=(rhs);
		return *this;
	}

	Boat::~Boat()
	{

	}

	Boatplane Boat::operator+(Airplane& plane)
	{
		return plane + *this;
	}

	size_t Boat::GetSailSpeed() const
	{
		size_t passengersCount{ GetPassengersCount() };
		size_t totalWeight{};

		for (size_t i{}; i < passengersCount; ++i)
		{
			totalWeight += GetPassenger(i)->GetWeight();
		}

		//MAX((800 - 10x), 20)

		return static_cast<size_t>(std::max<int>(800 - 10 * totalWeight, 20));
	}

	size_t Boat::GetMaxSpeed() const
	{
		return GetSailSpeed();
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