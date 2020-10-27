#include <cmath>

#include "Boatplane.h"

namespace assignment2
{
	Boatplane::Boatplane(unsigned int maxPassengersCount)
		: Vehicle{maxPassengersCount}
	{

	}

	Boatplane::Boatplane(const Boatplane& rhs)
		: Vehicle{ rhs }
	{

	}

	Boatplane& Boatplane::operator=(const Boatplane& rhs)
	{
		Vehicle::operator=(rhs);
		return *this;
	}

	Boatplane::~Boatplane()
	{

	}

	size_t Boatplane::GetMaxSpeed() const
	{
		size_t sailSpeed{ GetSailSpeed() };
		size_t flySpeed{ GetFlySpeed() };

		return (sailSpeed > flySpeed) ? sailSpeed : flySpeed;

	}

	size_t Boatplane::GetFlySpeed() const
	{
		size_t passengersCount{ GetPassengersCount() };
		size_t totalWeight{};

		for (size_t i{}; i < passengersCount; ++i)
		{
			totalWeight += GetPassenger(i)->GetWeight();
		}

		double power{ (static_cast<double>(totalWeight) * (-1) + 500) / 300 };

		size_t flySpeed{ static_cast<size_t>(std::floor(std::exp(power) * 150 + 0.5)) };

		//150 * e ^ ((-x + 500) / 300)

		return flySpeed;

	}

	size_t Boatplane::GetSailSpeed() const
	{
		size_t passengersCount{ GetPassengersCount() };
		size_t totalWeight{};

		for (size_t i{}; i < passengersCount; ++i)
		{
			totalWeight += GetPassenger(i)->GetWeight();
		}


		//MAX((800 - 1.7x), 20)

		return static_cast<size_t>(std::max<double>(800 - 1.7 * static_cast<double>(totalWeight), 20.0));
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