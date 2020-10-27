#pragma once
#include "Vehicle.h"
#include "ISailable.h"

namespace assignment2
{
	class UBoat : public Vehicle, public ISailable
	{
	public:
		UBoat();
		UBoat(const UBoat& rsh);
		UBoat& operator=(const UBoat& rhs);
		~UBoat();
	};
}
