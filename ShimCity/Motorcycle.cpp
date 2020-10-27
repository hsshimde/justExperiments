#include "Motorcycle.h"

namespace assignment2
{
	Motorcycle::Motorcycle()
		: Vehicle{2}
	{

	}


	Motorcycle::~Motorcycle()
	{

	}

	size_t Motorcycle::GetDriveSpeed() const
	{

	}

	size_t Motorcycle::GetMaxSpeed() const
	{
		
	}

	bool Motorcycle::GoOnTravel()
	{
		size_t travelCount{ GetTravelCount() };
		IncreaseTravelCount();

		if (travelCount % 6 == 0)
		{
			return false;
		}

		else
		{
			return true;
		}
	}
}