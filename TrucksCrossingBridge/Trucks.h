#pragma once
#include "Bridge.h"

namespace codingpractice
{
	class Bridge;

	class Truck
	{
	public:
		Truck(size_t weight, size_t startTime);
		Truck(const Truck& rhs);
		//~Truck();

		size_t GetWeight() const;
		size_t GetTime() const;

	private:
		size_t mWeight;
		size_t mBeginTime;


	};
}