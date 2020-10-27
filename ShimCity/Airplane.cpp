#include <cmath>

#include "Airplane.h"
#include "Boat.h"
#include "Boatplane.h"

namespace assignment2
{
	Airplane::Airplane(unsigned int maxPassengersCount)
		: Vehicle{ maxPassengersCount }
	{

	}

	Airplane::Airplane(const Airplane& rhs)
		: Vehicle{ rhs }
	{

	}

	Airplane& Airplane::operator=(const Airplane& rhs)
	{
		Vehicle::operator=(rhs);
		return *this;
	}

	Airplane::~Airplane()
	{

	}

	Boatplane Airplane::operator+(Boat& boat)
	{
		Boatplane bp{ GetMaxPassengersCount() + boat.GetMaxPassengersCount() };
		size_t passengersCountOnPlane{ GetPassengersCount() };
		size_t passengersCountOnBoat{ boat.GetPassengersCount() };

		for (size_t i{}; i < passengersCountOnPlane; ++i)
		{
			bp.AddPassenger(GetPassenger(i));
		}

		for (size_t i{}; i < passengersCountOnBoat; ++i)
		{
			bp.AddPassenger(boat.GetPassenger(i));
		}

		MakeVehicleEmpty();
		boat.MakeVehicleEmpty();

		return bp;
	}

	size_t Airplane::GetFlySpeed() const
	{
		size_t passengersCount{ GetPassengersCount() };
		size_t totalWeight{};

		for (size_t i{}; i < passengersCount; ++i)
		{
			totalWeight += GetPassenger(i)->GetWeight();
		}

		double power{ (static_cast<double>(totalWeight) * (-1) + 800) / 500 };

		size_t flySpeed{ static_cast<size_t>(std::floor(std::exp(power) * 200 + 0.5)) };

		//200 * e^((-x + 800) / 500)

		return flySpeed;


	}
	size_t Airplane::GetDriveSpeed() const
	{
		size_t passengersCount{ GetPassengersCount() };
		size_t totalWeight{};

		for (size_t i{}; i < passengersCount; ++i)
		{
			totalWeight += GetPassenger(i)->GetWeight();
		}

		double power{ (static_cast<double>(totalWeight) * (-1) + 400) / 70 };

		size_t driveSpeed{ static_cast<size_t>(std::floor(std::exp(power) * 4 + 0.5)) };

		return driveSpeed;
		//4 * e ^ ((-x + 400) / 70)

	}

	size_t Airplane::GetMaxSpeed() const
	{
		size_t flySpeed{ GetFlySpeed() };
		size_t driveSpeed{ GetDriveSpeed() };

		return (flySpeed > driveSpeed) ? flySpeed : driveSpeed;
	}

	bool Airplane::GoOnTravel()
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