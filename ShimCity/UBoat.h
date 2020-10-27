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
		virtual ~UBoat();

		size_t GetMaxSpeed() const;
		size_t GetSailSpeed() const;
		size_t GetDiveSpeed() const;
		bool GoOnTravel();
	};
}
