#include <cassert>
#include <cmath>

#include "Lawn.h"

namespace lab5
{
	Lawn::Lawn()
	{

	}

	Lawn::~Lawn()
	{

	}

	unsigned int Lawn::GetGrassPrice(eGrassType grasstype) const
	{
		double grassPricePerSquaredMeter{};

		switch (grasstype)
		{
		case eGrassType::BERMUDA:
			grassPricePerSquaredMeter = 8.0;
			break;

		case eGrassType::BAHIA:
			grassPricePerSquaredMeter = 5.0;
			break;

		case eGrassType::BENTGRASS:
			grassPricePerSquaredMeter = 3.0;
			break;

		case eGrassType::PERENNIAL_RYEGRASS:
			grassPricePerSquaredMeter = 2.5;
			break;

		case eGrassType::ST_AUGUSTINE:
			grassPricePerSquaredMeter = 4.5;
			break;

		default:
			assert((false, "unknown type"));
			break;

		}

		double area{ static_cast<double>(GetArea()) };

		size_t rollsCount{ GetMinimumSodRollsCount() };

		return static_cast<size_t>(std::floor(area * grassPricePerSquaredMeter + 0.5));
	}

	unsigned int Lawn::GetMinimumSodRollsCount() const
	{
		//0.3m2 for each sod roll
		double area{ static_cast<double>(GetArea()) };

		return static_cast<size_t>(std::ceil(area / 0.3));
	}
}