#pragma once
#include "Portfolio.h"

namespace compare
{

	using namespace portfolio;

	class CompareByPBR
	{

	public:
		CompareByPBR(size_t timeLength);
		bool operator()(const IndividualStock* lhs, const IndividualStock* rhs);


	private:
		size_t mTimeLength;
	};
}