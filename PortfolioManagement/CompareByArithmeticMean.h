#pragma once
#include "Portfolio.h"

namespace compare
{

	using namespace portfolio;

	class CompareByAriMean
	{

	public:
		CompareByAriMean(size_t mTimeLength);
		bool operator()(const IndividualStock* lhs, const IndividualStock* rhs);

	private:
		size_t mTimeLength;
	};
}