#include <cmath>
#include <cassert>
#include "UBoat.h"

namespace assignment2
{
	UBoat::UBoat()
		: Vehicle{ 50 }
	{

	}

	UBoat::UBoat(const UBoat& rhs)
		: Vehicle{ rhs }
	{

	}

	UBoat& UBoat::operator=(const UBoat& rhs)
	{
		Vehicle::operator=(rhs);
		return *this;
	}

	UBoat::~UBoat()
	{

	}

	size_t UBoat::GetDiveSpeed() const
	{
		size_t passengersCount{ GetPassengersCount() };
		size_t totalWeight{};

		for (size_t i{}; i < passengersCount; ++i)
		{
			totalWeight += GetPassenger(i)->GetWeight();
		}
		//500 * log((x + 150) / 150) + 30

		double diveSpeed{ 500 * std::log((static_cast<double>(totalWeight) + 150) / 150) + 30 };

		return static_cast<size_t>(std::floor(diveSpeed + 0.5));

	}

	size_t UBoat::GetSailSpeed() const
	{
		size_t passengersCount{ GetPassengersCount() };
		size_t totalWeight{};

		for (size_t i{}; i < passengersCount; ++i)
		{
			totalWeight += GetPassenger(i)->GetWeight();
		}

		//MAX((550 - x / 10), 200)

		double sailSpeed{ std::max<double>(550 - static_cast<double>(totalWeight) / 10, 200.0) };

		return static_cast<size_t>(std::floor(sailSpeed + 0.5));

	}

	size_t UBoat::GetMaxSpeed() const
	{
		size_t sailSpeed{ GetSailSpeed() };
		size_t diveSpeed{ GetDiveSpeed() };

		return (sailSpeed > diveSpeed) ? sailSpeed : diveSpeed;
	}

	bool UBoat::GoOnTravel()
	{
		size_t travelCount{ GetTravelCount() };
		IncreaseTravelCount();

		if (travelCount % 6 == 1 || travelCount % 6 == 2)
		{
			return true;
		}

		else
		{
			return false;
		}
	}


}