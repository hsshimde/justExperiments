#include <cmath>

#include "Motorcycle.h"

static double Exp(double number, size_t power);

namespace assignment2
{
	Motorcycle::Motorcycle()
		: Vehicle{2}
	{

	}

	Motorcycle::Motorcycle(const Motorcycle& rhs)
		: Vehicle{ rhs }
	{

	}

	Motorcycle& Motorcycle::operator=(const Motorcycle& rhs)
	{
		Vehicle::operator=(rhs);
		return *this;
	}


	Motorcycle::~Motorcycle()
	{

	}

	size_t Motorcycle::GetDriveSpeed() const
	{
		size_t passengersCount{ GetPassengersCount() };
		size_t totalWeight{};

		for (size_t i{}; i < passengersCount; ++i)
		{
			totalWeight += GetPassenger(i)->GetWeight();
		}

		//	MAX((-(x / 15) ^ 3 + 2x + 400), 0)

		double power3{ Exp(static_cast<double>(totalWeight) / 15, 3) };

		double max{ std::max<double>(power3 * (-1) + 2 * static_cast<double>(totalWeight) + 400, 0) };

		return static_cast<size_t>(std::floor(max + 0.5));
	}

	size_t Motorcycle::GetMaxSpeed() const
	{
		return GetDriveSpeed();
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

double Exp(double number, size_t power)
{
	double originalNumber{ number };

	for (size_t i{ 1 }; i < power; ++i)
	{
		number *= originalNumber;
	}

	return number;
}