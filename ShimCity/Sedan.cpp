#include <cassert>
#include "Sedan.h"

namespace assignment2
{
	Sedan::Sedan()
		: Vehicle{4}
		, mbConnected{ false }
		, mConnectedTrailer{}
	{

	}

	Sedan::Sedan(const Sedan& rhs)
		: Vehicle{ rhs }
		, mbConnected{ rhs.mbConnected }
		, mConnectedTrailer{}
	{
		if (mbConnected)
		{
			mConnectedTrailer = new Trailer{ rhs.mConnectedTrailer->GetWeight() };
		}

	}

	Sedan& Sedan::operator=(const Sedan& rhs)
	{
		Vehicle::operator=(rhs);
		if (rhs.mbConnected)
		{
			if (mbConnected)
			{
				delete mConnectedTrailer;
			}

			mConnectedTrailer = new Trailer{ rhs.mConnectedTrailer->GetWeight() };
		}

		else
		{
			if (mbConnected)
			{
				delete mConnectedTrailer;
				mbConnected = false;
			}
		}

		return *this;
	}

	Sedan::~Sedan()
	{
		if (mbConnected)
		{
			delete mConnectedTrailer;
		}
	}

	bool Sedan::AddTrailer(const Trailer* trailer)
	{
		assert(trailer != nullptr);

		if (mbConnected)
		{
			return false;
		}
		else
		{
			mbConnected = true;
			mConnectedTrailer = trailer;
		}
	}

	bool Sedan::RemoveTrailer()
	{
		if (!mbConnected)
		{
			return false;
		}

		else
		{
			delete mConnectedTrailer;
			mbConnected = false;
		}
	}

	size_t Sedan::GetMaxSpeed() const
	{
		return GetDriveSpeed();
	}

	size_t Sedan::GetDriveSpeed() const
	{
		size_t passengersCount{ GetPassengersCount() };
		size_t totalWeight{};

		for (size_t i{}; i < passengersCount; ++i)
		{
			totalWeight += GetPassenger(i)->GetWeight();
		}

		if (mbConnected)
		{
			totalWeight += mConnectedTrailer->GetWeight();
		}

		if (totalWeight <= 80)
		{
			return 480;
		}

		else if (totalWeight > 80 && totalWeight <= 160)
		{
			return 458;
		}

		else if (totalWeight > 160 && totalWeight <= 260)
		{
			return 400;
		}

		else if (totalWeight > 260 && totalWeight <= 350)
		{
			return 380;
		}

		else
		{
			return 300;
		}

	}

	bool Sedan::GoOnTravel()
	{
		size_t travelCount{ GetTravelCount() };
		IncreaseTravelCount();

		if (mbConnected)
		{
			if (travelCount % 6 == 0)
			{
				return false;
			}

			else
			{
				return true;
			}
		}

		else
		{
			if (travelCount % 7 == 0 || (travelCount + 1) % 7 == 0)
			{
				return false;
			}

			else
			{
				return true;
			}

		}

		
	}
}