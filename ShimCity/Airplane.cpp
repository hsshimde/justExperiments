#include "Airplane.h"
#include "Boat.h"
#include "Boatplane.h"

namespace assignment2
{
	Airplane::Airplane(unsigned int maxPassengersCount)
		: Vehicle{ maxPassengersCount }
	{

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
		bp.MakeVehicleEmpty();

		return bp;
	}

	size_t Airplane::GetDriveSpeed() const
	{

	}

	size_t Airplane::GetFlySpeed() const
	{

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