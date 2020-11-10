#pragma once
#include "Portfolio.h"

namespace compare
{

	using namespace portfolio;

	class CompareByGeoMean
	{

	public:
		bool operator()(const IndividualStock* lhs, const IndividualStock* rhs);
	};
}