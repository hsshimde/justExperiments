#pragma once
#include "Portfolio.h"

namespace compare
{
	
	using namespace portfolio;

	class CompareByMarketCap
	{

	public:
		CompareByMarketCap(size_t timeLength);
		bool operator()(const IndividualStock* lhs, const IndividualStock* rhs);

	private:
		size_t mTimeLength;
	};
}