#pragma once
#include "Portfolio.h"

namespace compare
{
	
	using namespace portfolio;

	class CompareByMarketCap
	{

	public:
		bool operator()(const IndividualStock* lhs, const IndividualStock* rhs);

	};
}