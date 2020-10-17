#include <vector>


#include "Trucks.h"	

namespace codingpractice
{
	Truck::Truck(size_t weight, size_t beginTime)
		: mWeight{ weight }
		, mBeginTime{ beginTime }
	{

	}

	Truck::Truck(const Truck& rhs)
		: mWeight{ rhs.mWeight }
		, mBeginTime{ rhs.mBeginTime }
	{

	}

	Truck::~Truck()
	{

	}


	size_t Truck::GetTime() const
	{
		return mBeginTime;
	}
	
	size_t Truck::GetWeight() const
	{
		return mWeight;
	}
	//everyone is struggling, everyone has their own problem on their own....
	
	
	size_t Truck::GetWeight() const
	{
		return mWeight;
	}
}