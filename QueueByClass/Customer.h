#pragma once

using longSize_t = unsigned long int;

namespace customer
{


	class Customer
	{

	public:
		Customer();
		void SetArriveTime(longSize_t time);
		longSize_t GetArriveTime() const;
		size_t GetProcessTime() const;

	private:
		longSize_t mArriveTime;
		size_t mProcessTime;

	};

}