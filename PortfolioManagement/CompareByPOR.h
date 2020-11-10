#pragma once
#include "Portfolio.h"

namespace compare
{

	using namespace portfolio;

	class CompareByPOR
	{

	public:
		CompareByPOR(size_t timeLength);
		bool operator()(const IndividualStock* lhs, const IndividualStock* rhs);


	private:
		size_t mTimeLength
	};
}