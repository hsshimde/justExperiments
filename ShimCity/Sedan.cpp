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

	Sedan::~Sedan()
	{
		if (mbConnected)
		{
			delete mConnectedTrailer;
		}
	}

	bool Sedan::AddTrailer(const Trailer* trailer)
	{
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
			mbConnected = false;
			delete mConnectedTrailer;
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