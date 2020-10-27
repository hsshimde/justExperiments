#pragma once
#include "Vehicle.h"
#include "IFlyable.h"
#include "ISailable.h"

namespace assignment2
{
	class  Boatplane : public Vehicle, public IFlyable, public ISailable
	{
	public:
		Boatplane(unsigned int maxPassengersCount);
		Boatplane(const Boatplane& rhs);
		Boatplane& operator=(const Boatplane& rhs);
		virtual ~Boatplane();

		virtual size_t GetMaxSpeed() const;
		virtual size_t GetFlySpeed() const;
		virtual size_t GetSailSpeed() const;
		virtual bool GoOnTravel();
		


	};
}