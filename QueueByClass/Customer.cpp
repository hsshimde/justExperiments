#include <random>
#include "Customer.h"

namespace customer
{
	Customer::Customer()
		:mArriveTime{ 0 }
		, mProcessTime{ 0 }
	{

	}


	void Customer::SetArriveTime(longSize_t time)
	{
		mProcessTime = std::rand() % 3 + 1;
		mArriveTime = time;
	}

	longSize_t Customer::GetArriveTime() const
	{
		return mArriveTime;
	}


	size_t Customer::GetProcessTime() const
	{
		return mProcessTime;
	}

}