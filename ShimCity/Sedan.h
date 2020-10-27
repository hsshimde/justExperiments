#pragma once
#include "Vehicle.h"
#include "IDrivable.h"	
#include "Trailer.h"	

namespace assignment2
{
	class Trailer;

	class Sedan : public Vehicle, public IDrivable
	{
	public:
		Sedan();
		Sedan(const Sedan& rhs);
		Sedan& operator=(const Sedan& rhs);
		virtual ~Sedan();

		bool AddTrailer(const Trailer* trailer);
		bool RemoveTrailer();
		bool GoOnTravel();

		size_t GetMaxSpeed() const;
		size_t GetDriveSpeed() const;

	private:
		const Trailer* mConnectedTrailer;
		bool mbConnected;
		

	};
}